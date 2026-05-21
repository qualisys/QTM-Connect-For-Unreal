// QTM Connect For Unreal. Copyright 2018-2026 Qualisys
//
#include "QTMRecordingController.h"

#include "QTMConnectLiveLinkLog.h"
#include "HAL/PlatformProcess.h"
#include "Logging/StructuredLog.h"

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#endif
#include "RTClientSDK/RTPacket.h"
#include "RTClientSDK/RTProtocol.h"
#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include <string>

#define LOCTEXT_NAMESPACE "QTMRecordingController"

namespace
{
    constexpr int32 kMaxSaveAttempts = 20;       // ~10 s at 500 ms backoff
    constexpr double kSaveBackoffSeconds = 0.5;
    constexpr int32 kReceiveTimeoutMs = 200;      // worker idle-loop tick
}

FQTMRecordingController::FQTMRecordingController()
{
    StatusText = LOCTEXT("Status_Idle", "Idle");
    Thread = FRunnableThread::Create(this, TEXT("FQTMRecordingController"));
}

FQTMRecordingController::~FQTMRecordingController()
{
    if (Thread)
    {
        CommandQueue.Enqueue({ECommand::Shutdown});
        Stop();
        Thread->WaitForCompletion();
        delete Thread;
        Thread = nullptr;
    }
}

void FQTMRecordingController::Stop()
{
    bStopRequested = true;
}

void FQTMRecordingController::RequestConnect(const FString& Host, uint16 Port, const FString& Password)
{
    FCommand Cmd;
    Cmd.Op = ECommand::Connect;
    Cmd.StringArg1 = Host;
    Cmd.StringArg2 = Password;
    Cmd.IntArg = Port;
    CommandQueue.Enqueue(MoveTemp(Cmd));
}

void FQTMRecordingController::RequestDisconnect()
{
    CommandQueue.Enqueue({ECommand::Disconnect});
}

void FQTMRecordingController::RequestStartRecording()
{
    CommandQueue.Enqueue({ECommand::StartRecording});
}

void FQTMRecordingController::RequestStopRecording(const FString& SaveTargetPath)
{
    FCommand Cmd;
    Cmd.Op = ECommand::StopRecording;
    Cmd.StringArg1 = SaveTargetPath;
    CommandQueue.Enqueue(MoveTemp(Cmd));
}

FText FQTMRecordingController::GetStatusText() const
{
    FScopeLock Lock(&StatusLock);
    return StatusText;
}

FString FQTMRecordingController::GetLastSavedPath() const
{
    FScopeLock Lock(&StatusLock);
    return LastSavedPath;
}

void FQTMRecordingController::SetStatusText(const FText& InText)
{
    FScopeLock Lock(&StatusLock);
    StatusText = InText;
}

void FQTMRecordingController::SetStatus(EQTMControllerStatus InStatus)
{
    Status = InStatus;
}

uint32 FQTMRecordingController::Run()
{
    while (!bStopRequested)
    {
        // Drain any queued commands.
        FCommand Cmd;
        while (CommandQueue.Dequeue(Cmd))
        {
            switch (Cmd.Op)
            {
                case ECommand::Connect:        Worker_Connect(Cmd); break;
                case ECommand::Disconnect:     Worker_Disconnect(); break;
                case ECommand::StartRecording: Worker_StartRecording(); break;
                case ECommand::StopRecording:  Worker_StopRecording(Cmd.StringArg1); break;
                case ECommand::Shutdown:       bStopRequested = true; break;
            }
            if (bStopRequested) break;
        }

        if (RTProtocol && RTProtocol->Connected())
        {
            Worker_PumpEvents();

            if (bSavePending && FPlatformTime::Seconds() >= NextSaveAttemptSeconds)
            {
                Worker_AttemptSave();
            }
        }
        else
        {
            FPlatformProcess::Sleep(0.05f);
        }
    }

    Worker_Disconnect();
    return 0;
}

void FQTMRecordingController::Worker_Connect(const FCommand& Cmd)
{
    if (RTProtocol && RTProtocol->Connected())
    {
        return;
    }

    SetStatus(EQTMControllerStatus::Connecting);
    SetStatusText(LOCTEXT("Status_Connecting", "Connecting"));

    RTProtocol = std::make_shared<CRTProtocol>();

    const std::string Host(TCHAR_TO_ANSI(*Cmd.StringArg1));
    constexpr unsigned short kQTMRTPort = 22222;
    const unsigned short Port = Cmd.IntArg != 0 ? Cmd.IntArg : kQTMRTPort;

    if (!RTProtocol->Connect(Host.c_str(), Port))
    {
        const FString Err = ANSI_TO_TCHAR(RTProtocol->GetErrorString());
        const int32 PortLogged = static_cast<int32>(Port);
        UE_LOGFMT(QTMConnectLiveLinkLog, Warning, "Connect to {Host}:{Port} failed: {Error}",
            Cmd.StringArg1, PortLogged, Err);
        SetStatusText(FText::Format(LOCTEXT("Status_ConnectFailed", "Connect failed: {0}"), FText::FromString(Err)));
        RTProtocol.reset();
        SetStatus(EQTMControllerStatus::Disconnected);
        return;
    }

    const std::string Password(TCHAR_TO_ANSI(*Cmd.StringArg2));
    if (!RTProtocol->TakeControl(Password))
    {
        const FString Err = ANSI_TO_TCHAR(RTProtocol->GetErrorString());
        UE_LOGFMT(QTMConnectLiveLinkLog, Warning, "TakeControl failed: {Error}", Err);
        SetStatusText(FText::Format(LOCTEXT("Status_TakeControlFailed", "TakeControl failed: {0}"), FText::FromString(Err)));
        RTProtocol->Disconnect();
        RTProtocol.reset();
        SetStatus(EQTMControllerStatus::Disconnected);
        return;
    }

    SetStatus(EQTMControllerStatus::Connected);
    SetStatusText(LOCTEXT("Status_Connected", "Connected, in control"));
}

void FQTMRecordingController::Worker_Disconnect()
{
    if (!RTProtocol)
    {
        SetStatus(EQTMControllerStatus::Disconnected);
        return;
    }

    SetStatus(EQTMControllerStatus::Disconnecting);

    if (bIsRecording)
    {
        // Best-effort: stop the capture but don't try to save (caller didn't ask for it here).
        RTProtocol->StopCapture();
        bIsRecording = false;
    }
    bSavePending = false;

    if (RTProtocol->Connected())
    {
        RTProtocol->ReleaseControl();
        RTProtocol->Disconnect();
    }
    RTProtocol.reset();

    SetStatus(EQTMControllerStatus::Disconnected);
    SetStatusText(LOCTEXT("Status_Idle", "Idle"));
}

void FQTMRecordingController::Worker_StartRecording()
{
    if (!RTProtocol || !RTProtocol->Connected())
    {
        SetStatusText(LOCTEXT("Status_NotConnected", "Not connected"));
        return;
    }
    if (bIsRecording)
    {
        return;
    }

    if (!RTProtocol->NewMeasurement())
    {
        const FString Err = ANSI_TO_TCHAR(RTProtocol->GetErrorString());
        UE_LOGFMT(QTMConnectLiveLinkLog, Warning, "NewMeasurement failed: {Error}", Err);
        SetStatusText(FText::Format(LOCTEXT("Status_NewMeasFailed", "NewMeasurement failed: {0}"), FText::FromString(Err)));
        return;
    }

    if (!RTProtocol->StartCapture())
    {
        const FString Err = ANSI_TO_TCHAR(RTProtocol->GetErrorString());
        UE_LOGFMT(QTMConnectLiveLinkLog, Warning, "StartCapture failed: {Error}", Err);
        SetStatusText(FText::Format(LOCTEXT("Status_StartFailed", "StartCapture failed: {0}"), FText::FromString(Err)));
        // NewMeasurement opened a measurement we should now close.
        RTProtocol->CloseMeasurement();
        return;
    }

    bIsRecording = true;
    SetStatusText(LOCTEXT("Status_Recording", "Recording"));
}

void FQTMRecordingController::Worker_StopRecording(const FString& SaveTargetPath)
{
    if (!RTProtocol || !RTProtocol->Connected() || !bIsRecording)
    {
        return;
    }

    if (!RTProtocol->StopCapture())
    {
        const FString Err = ANSI_TO_TCHAR(RTProtocol->GetErrorString());
        UE_LOGFMT(QTMConnectLiveLinkLog, Warning, "StopCapture failed: {Error}", Err);
        SetStatusText(FText::Format(LOCTEXT("Status_StopFailed", "StopCapture failed: {0}"), FText::FromString(Err)));
        return;
    }

    bIsRecording = false;
    SetStatusText(LOCTEXT("Status_Saving", "Capture stopped, preparing to save"));

    // Queue a save. We wait for EventCaptureStopped in Worker_PumpEvents before
    // the first attempt; if that never arrives we still retry on the backoff.
    bSavePending = true;
    PendingSavePath = SaveTargetPath;
    SaveAttempt = 0;
    NextSaveAttemptSeconds = FPlatformTime::Seconds() + kSaveBackoffSeconds;
}

void FQTMRecordingController::Worker_PumpEvents()
{
    CRTPacket::EPacketType PacketType;
    const int Result = RTProtocol->ReceiveRTPacket(PacketType, false, kReceiveTimeoutMs);

    if (Result <= 0)
    {
        // 0 == timeout, <0 == error/disconnect.
        if (Result < 0)
        {
            UE_LOGFMT(QTMConnectLiveLinkLog, Warning, "RT packet read failed; connection lost");
            SetStatusText(LOCTEXT("Status_LostConnection", "Connection lost"));
            RTProtocol->Disconnect();
            RTProtocol.reset();
            SetStatus(EQTMControllerStatus::Disconnected);
            bIsRecording = false;
            bSavePending = false;
        }
        return;
    }

    if (PacketType != CRTPacket::PacketEvent)
    {
        return;
    }

    CRTPacket* Packet = RTProtocol->GetRTPacket();
    if (!Packet)
    {
        return;
    }

    CRTPacket::EEvent Event;
    if (!Packet->GetEvent(Event))
    {
        return;
    }

    switch (Event)
    {
        case CRTPacket::EventCaptureStarted:
            bIsRecording = true;
            break;
        case CRTPacket::EventCaptureStopped:
            bIsRecording = false;
            if (bSavePending)
            {
                // File should be ready now; attempt save immediately.
                NextSaveAttemptSeconds = FPlatformTime::Seconds();
            }
            break;
        case CRTPacket::EventConnectionClosed:
        case CRTPacket::EventQTMShuttingDown:
            UE_LOGFMT(QTMConnectLiveLinkLog, Warning, "QTM closed the connection");
            SetStatusText(LOCTEXT("Status_QTMClosed", "QTM closed the connection"));
            if (RTProtocol)
            {
                RTProtocol->Disconnect();
                RTProtocol.reset();
            }
            SetStatus(EQTMControllerStatus::Disconnected);
            bIsRecording = false;
            bSavePending = false;
            break;
        default:
            break;
    }
}

void FQTMRecordingController::Worker_AttemptSave()
{
    if (!bSavePending || !RTProtocol || !RTProtocol->Connected())
    {
        bSavePending = false;
        return;
    }

    ++SaveAttempt;

    // SaveCapture: empty target -> QTM uses its current project directory + default name.
    // The SDK writes the actual filename used (after dedupe) into ResolvedName.
    const std::string TargetUtf8(TCHAR_TO_ANSI(*PendingSavePath));
    std::string ResolvedName;

    const bool bSaved = RTProtocol->SaveCapture(
        TargetUtf8,
        /*overwrite=*/false,
        &ResolvedName,
        /*sizeOfNewFileName=*/0);

    if (bSaved)
    {
        const FString SavedAs = !ResolvedName.empty()
            ? FString(ANSI_TO_TCHAR(ResolvedName.c_str()))
            : PendingSavePath;
        {
            FScopeLock Lock(&StatusLock);
            LastSavedPath = SavedAs;
            StatusText = FText::Format(LOCTEXT("Status_Saved", "Saved: {0}"), FText::FromString(SavedAs));
        }
        UE_LOGFMT(QTMConnectLiveLinkLog, Log, "Saved capture as {Path}", SavedAs);

        // Close the measurement now that it's saved.
        RTProtocol->CloseMeasurement();
        bSavePending = false;
        SaveAttempt = 0;
        return;
    }

    const FString Err = ANSI_TO_TCHAR(RTProtocol->GetErrorString());

    if (SaveAttempt >= kMaxSaveAttempts)
    {
        UE_LOGFMT(QTMConnectLiveLinkLog, Error, "SaveCapture giving up after {N} attempts: {Error}", SaveAttempt, Err);
        SetStatusText(FText::Format(LOCTEXT("Status_SaveFailed", "Save failed: {0}"), FText::FromString(Err)));
        // Close the measurement so QTM isn't left in a half-state.
        RTProtocol->CloseMeasurement();
        bSavePending = false;
        SaveAttempt = 0;
        return;
    }

    UE_LOGFMT(QTMConnectLiveLinkLog, Verbose, "SaveCapture attempt {N} failed, retrying: {Error}", SaveAttempt, Err);
    NextSaveAttemptSeconds = FPlatformTime::Seconds() + kSaveBackoffSeconds;
}

#undef LOCTEXT_NAMESPACE
