// QTM Connect For Unreal. Copyright 2018-2026 Qualisys
//
#include "QTMLiveLinkDevice.h"

#include "QTMLiveLinkDeviceLog.h"
#include "QTMRecordingController.h"

// UE 5.8 moved this header from LiveLinkHub to LiveLinkInterface and renamed the class.
#include "LiveLinkHub/ILiveLinkRecordingSession.h"
#include "Internationalization/Regex.h"
#include "Logging/StructuredLog.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "QTMLiveLinkDevice"


namespace
{
    /** Translate the runtime controller's status to the LiveLinkDevice capability enum. */
    ELiveLinkDeviceConnectionStatus ToLiveLinkStatus(EQTMControllerStatus In)
    {
        switch (In)
        {
            case EQTMControllerStatus::Connecting:    return ELiveLinkDeviceConnectionStatus::Connecting;
            case EQTMControllerStatus::Connected:     return ELiveLinkDeviceConnectionStatus::Connected;
            case EQTMControllerStatus::Disconnecting: return ELiveLinkDeviceConnectionStatus::Disconnecting;
            case EQTMControllerStatus::Disconnected:
            default:                                  return ELiveLinkDeviceConnectionStatus::Disconnected;
        }
    }
}


EDeviceHealth UQTMLiveLinkDevice::GetDeviceHealth() const
{
    if (!Controller.IsValid())
    {
        return EDeviceHealth::Info;
    }

    switch (Controller->GetStatus())
    {
        case EQTMControllerStatus::Connected:
            return Controller->IsRecording() ? EDeviceHealth::Good : EDeviceHealth::Nominal;
        case EQTMControllerStatus::Connecting:
        case EQTMControllerStatus::Disconnecting:
            return EDeviceHealth::Info;
        case EQTMControllerStatus::Disconnected:
        default:
            return EDeviceHealth::Warning;
    }
}

FText UQTMLiveLinkDevice::GetHealthText() const
{
    if (!Controller.IsValid())
    {
        return LOCTEXT("Health_NotInitialized", "Not initialized");
    }
    return Controller->GetStatusText();
}

void UQTMLiveLinkDevice::OnDeviceAdded()
{
    Super::OnDeviceAdded();
    Controller = MakeUnique<FQTMRecordingController>();
}

void UQTMLiveLinkDevice::OnDeviceRemoved()
{
    // Destructor blocks on thread completion.
    Controller.Reset();
    Super::OnDeviceRemoved();
}

// --- Connection capability ---------------------------------------------------

ELiveLinkDeviceConnectionStatus UQTMLiveLinkDevice::GetConnectionStatus_Implementation() const
{
    return Controller.IsValid()
        ? ToLiveLinkStatus(Controller->GetStatus())
        : ELiveLinkDeviceConnectionStatus::Disconnected;
}

FString UQTMLiveLinkDevice::GetHardwareId_Implementation() const
{
    const UQTMLiveLinkDeviceSettings* S = GetDeviceSettings<UQTMLiveLinkDeviceSettings>();
    return FString::Printf(TEXT("%s:%d"), *S->Host, S->Port);
}

bool UQTMLiveLinkDevice::SetHardwareId_Implementation(const FString& HardwareID)
{
    UQTMLiveLinkDeviceSettings* S = GetDeviceSettings<UQTMLiveLinkDeviceSettings>();

    FString Host;
    FString PortStr;
    if (HardwareID.Split(TEXT(":"), &Host, &PortStr))
    {
        const int32 Port = FCString::Atoi(*PortStr);
        if (Port <= 0 || Port > 65535)
        {
            return false;
        }
        S->Host = Host;
        S->Port = Port;
    }
    else
    {
        // Just a host, keep current port.
        S->Host = HardwareID;
    }
    return true;
}

bool UQTMLiveLinkDevice::Connect_Implementation()
{
    if (!Controller.IsValid())
    {
        return false;
    }
    const UQTMLiveLinkDeviceSettings* S = GetDeviceSettings<UQTMLiveLinkDeviceSettings>();
    Controller->RequestConnect(S->Host, (uint16)S->Port, S->Password);
    SetConnectionStatus(ELiveLinkDeviceConnectionStatus::Connecting);
    return true;
}

bool UQTMLiveLinkDevice::Disconnect_Implementation()
{
    if (!Controller.IsValid())
    {
        return false;
    }
    Controller->RequestDisconnect();
    SetConnectionStatus(ELiveLinkDeviceConnectionStatus::Disconnecting);
    return true;
}

// --- Recording capability ----------------------------------------------------

bool UQTMLiveLinkDevice::StartRecording_Implementation()
{
    if (!Controller.IsValid())
    {
        return false;
    }
    if (Controller->GetStatus() != EQTMControllerStatus::Connected)
    {
        UE_LOGFMT(LogQTMLiveLinkDevice, Warning, "StartRecording requested but device not connected");
        return false;
    }

    Controller->RequestStartRecording();
    return true;
}

bool UQTMLiveLinkDevice::StopRecording_Implementation()
{
    if (!Controller.IsValid())
    {
        return false;
    }
    const FString Destination = BuildDestinationPath();
    Controller->RequestStopRecording(Destination);
    return true;
}

bool UQTMLiveLinkDevice::IsRecording_Implementation() const
{
    return Controller.IsValid() && Controller->IsRecording();
}

// --- Filename templating -----------------------------------------------------

FString UQTMLiveLinkDevice::BuildDestinationPath() const
{
    const UQTMLiveLinkDeviceSettings* S = GetDeviceSettings<UQTMLiveLinkDeviceSettings>();

    ILiveLinkRecordingSession& Session = ILiveLinkRecordingSession::Get();
    const FString Slate = Session.GetSlateName();
    const FString SessionName = Session.GetSessionName();
    const int32 Take = Session.GetTakeNumber();

    FString Result = S->FilenameTemplate;

    // {Slate}, {Session}, {Take}
    Result.ReplaceInline(TEXT("{Slate}"), *Slate, ESearchCase::CaseSensitive);
    Result.ReplaceInline(TEXT("{Session}"), *SessionName, ESearchCase::CaseSensitive);
    Result.ReplaceInline(TEXT("{Take}"), *FString::FromInt(Take), ESearchCase::CaseSensitive);

    // {Take:Nd} — zero-padded
    const FRegexPattern Pattern(TEXT("\\{Take:(\\d+)d\\}"));
    FRegexMatcher Matcher(Pattern, Result);
    while (Matcher.FindNext())
    {
        const FString FullMatch = Result.Mid(Matcher.GetMatchBeginning(), Matcher.GetMatchEnding() - Matcher.GetMatchBeginning());
        const int32 Width = FCString::Atoi(*Matcher.GetCaptureGroup(1));
        const FString Padded = FString::Printf(TEXT("%0*d"), Width, Take);
        Result.ReplaceInline(*FullMatch, *Padded, ESearchCase::CaseSensitive);
        // Reset matcher: ReplaceInline invalidates indices.
        Matcher = FRegexMatcher(Pattern, Result);
    }

    // Sanitize: strip path-illegal chars conservatively.
    static const TCHAR* IllegalChars = TEXT("<>:\"|?*");
    for (const TCHAR* C = IllegalChars; *C; ++C)
    {
        const TCHAR ToReplace[2] = { *C, TEXT('\0') };
        Result.ReplaceInline(ToReplace, TEXT("_"), ESearchCase::CaseSensitive);
    }

    if (!S->CaptureDirectoryOverride.IsEmpty())
    {
        Result = FPaths::Combine(S->CaptureDirectoryOverride, Result);
    }
    // If override empty -> return bare filename so SaveCapture lands in QTM's project dir.

    return Result;
}

#undef LOCTEXT_NAMESPACE
