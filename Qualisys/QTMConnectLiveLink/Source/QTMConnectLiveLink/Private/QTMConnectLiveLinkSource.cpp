// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
#include "QTMConnectLiveLinkSource.h"
#include "ILiveLinkClient.h"
#include "LiveLinkTypes.h"
#include "Roles/LiveLinkAnimationRole.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#include "RTProtocol.h"
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
#include "CommonFrameRates.h"

#include <string>

#define LOCTEXT_NAMESPACE "QTMConnectLiveLinkSource"

#define QTM_STREAMING_PORT 22222

const FName markersParentName = "Markers";

#pragma optimize("", off)

QTMConnectLiveLinkSettings QTMConnectLiveLinkSettings::FromString(const FString& settingsString)
{
    QTMConnectLiveLinkSettings settings;
    if (!FParse::Value(*settingsString, TEXT("IpAddress="), settings.IpAddress))
    {
        settings.IpAddress = "127.0.0.1";
    }
    settings.AutoDiscover = false;
    FString autoDiscover;
    if (!FParse::Value(*settingsString, TEXT("AutoDiscover="), autoDiscover))
    {
        if (autoDiscover == "true")
            settings.AutoDiscover = true;
    }
    return settings;
}

FString QTMConnectLiveLinkSettings::ToString() const
{
    FString settingsString = FString::Printf(TEXT("IpAddress=\"%s\""), *IpAddress);
    settingsString.Append(FString::Printf(TEXT("AutoDiscover=\"%d\""), AutoDiscover ? TEXT("true") : TEXT("false")));
    return settingsString;
}

FQTMConnectLiveLinkSource::FQTMConnectLiveLinkSource(const QTMConnectLiveLinkSettings& settings)
    : Settings(settings)
    , Stopping(false)
    , Thread(nullptr)
{
    SourceType = LOCTEXT("QTMConnectLiveLinkSourceType", "QTM Connect LiveLink");
    SourceStatus = LOCTEXT("SourceStatus_NotConnected", "Not connected");
}

FQTMConnectLiveLinkSource::~FQTMConnectLiveLinkSource()
{
    Stop();

    ClearSubjects();

    if (Thread != nullptr)
    {
        Thread->WaitForCompletion();
        delete Thread;
        Thread = nullptr;
    }

    DisconnectFromQTM();

}

void FQTMConnectLiveLinkSource::DisconnectFromQTM()
{
    if (mRTProtocol != nullptr)
    {
        mRTProtocol->StreamFramesStop();
        mRTProtocol->Disconnect();
        mRTProtocol.reset();
    }
}

void FQTMConnectLiveLinkSource::ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid)
{
    Client = InClient;
    SourceGuid = InSourceGuid;

    Start();
}


bool FQTMConnectLiveLinkSource::IsSourceStillValid() const
{
    // Source is valid if we have a valid thread
    bool bIsSourceValid = !Stopping && Thread != nullptr;

    // And connected to QTM
    bool isConnected = mRTProtocol != nullptr && mRTProtocol->Connected();

    return bIsSourceValid && isConnected;
}


bool FQTMConnectLiveLinkSource::RequestSourceShutdown()
{
    Stop();

    return true;
}
// FRunnable interface

void FQTMConnectLiveLinkSource::Start()
{
    Thread = FRunnableThread::Create(this, TEXT("FQTMConnectLiveLinkSourceThread"));
}

void FQTMConnectLiveLinkSource::Stop()
{
    Stopping = true;

    SourceStatus = LOCTEXT("SourceStatus_NotConnected", "Not connected");
}

// NOTE: From David.Hibbitts@epicgames.com
// 1. Unfortunately the live link system is not tied to any specific world
// so for example you could run into an issue where multiple worlds are loaded
// at the same time and you would need to determine which world you are actually interested in.
// I am looking into if there's a clever way around this but for now I think the easiest way about
// this is to just add a property to your settings struct and then make a blueprint function library
// in your plugin which has a function to set that property. The user then just does something like OnBeginPlay -> GetWorldToMeters -> SetLiveLinkPluginWorldToMeters

float QtmToUEScalingFactor()
{
    // QTM uses mm and UE uses cm by default.
    // NOTE: This doesn't take into account WorldToMeters settings in UE.
    return 0.1f;
}


void ConstructLiveLinkTimeCode(int rate, int hours, int minutes, int seconds, int frames, FQualifiedFrameTime& timeCode)
{
    timeCode.Rate = FFrameRate(rate, 1);
    FTimecode UnrealTimecode(hours, minutes, seconds, frames, false);

    timeCode.Time = FFrameTime(UnrealTimecode.ToFrameNumber(timeCode.Rate));
}

void ConstructLiveLinkTimeCode(int rate, int seconds, FQualifiedFrameTime& timeCode)
{
    FTimecode UnrealTimecode(seconds, timeCode.Rate, false, true);
    timeCode.Time = FFrameTime(UnrealTimecode.ToFrameNumber(timeCode.Rate));
}

float CalculateTimecodeFrequency(std::shared_ptr<CRTProtocol> rtProtocol)
{
    if (rtProtocol == nullptr)
        return 0.0f;

    uint32_t frequency;
    float captureTime;
    bool startOnTrig;
    bool trigNo;
    bool trigNc;
    bool trigSoftware;
    CRTProtocol::EProcessingActions eProcessingActions;
    CRTProtocol::EProcessingActions eRtProcessingActions;
    CRTProtocol::EProcessingActions eReprocessingActions;

    rtProtocol->GetSystemSettings(frequency, captureTime, startOnTrig, trigNo, trigNc, trigSoftware, eProcessingActions, eRtProcessingActions, eReprocessingActions);

    bool bEnabled; CRTProtocol::ESignalSource eSignalSource;
    bool bSignalModePeriodic; unsigned int nFreqMultiplier;
    unsigned int nFreqDivisor; unsigned int nFreqTolerance;
    float fNominalFrequency; bool bNegativeEdge;
    unsigned int nSignalShutterDelay; float fNonPeriodicTimeout;
    rtProtocol->GetExtTimeBaseSettings(bEnabled, eSignalSource, bSignalModePeriodic, nFreqMultiplier, nFreqDivisor, nFreqTolerance, fNominalFrequency, bNegativeEdge, nSignalShutterDelay, fNonPeriodicTimeout);
    if (bEnabled)
    {
        // Calculate ext lock frequency
        return (float)frequency * (float)nFreqDivisor / (float)nFreqMultiplier;
    }
    return frequency;
}

uint32 FQTMConnectLiveLinkSource::Run()
{
    // mm to m to world scale
    const float positionScalingFactor = QtmToUEScalingFactor();

    bool readSettings = false;
    bool startedStreaming = false;

    float timecodeFrequency = 24;

    bool autoDiscover = Settings.AutoDiscover;
    std::string serverAddress(TCHAR_TO_ANSI(*(Settings.IpAddress)));

    while (!Stopping)
    {
        if (mRTProtocol == nullptr)
        {
            mRTProtocol = std::make_shared<CRTProtocol>();
        }
        if (!mRTProtocol->Connected())
        {
            if (autoDiscover)
            {
                if (mRTProtocol->DiscoverRTServer(0, false))
                {
                    const auto discoverResponses = mRTProtocol->GetNumberOfDiscoverResponses();
                    if (discoverResponses >= 1)
                    {
                        char message[256];
                        unsigned int addr;
                        unsigned short basePort;
                        if (mRTProtocol->GetDiscoverResponse(0, addr, basePort, message, sizeof(message)))
                        {
                            char serverAddr[40];
                            sprintf_s(serverAddr, "%d.%d.%d.%d", 0xff & addr, 0xff & (addr >> 8), 0xff & (addr >> 16), 0xff & (addr >> 24));
                            serverAddress = serverAddr;
                        }
                    }
                }
            }
            SourceMachineName = FText::FromString(serverAddress.c_str());

            unsigned short udpPort = 0;
            if (!mRTProtocol->Connect(serverAddress.c_str(), QTM_STREAMING_PORT))
            {
                SourceStatus = FText::FromString(ANSI_TO_TCHAR(mRTProtocol->GetErrorString()));

                FPlatformProcess::Sleep(1.0f);
                continue;
            }

            SourceStatus = LOCTEXT("SourceStatus_Connected", "Connected to QTM");
        }

        if (!readSettings)
        {
            bool any3DSettings = false;
            bool anySkeletonSettings = false;
            bool any6DOFSettings = false;
            if (mRTProtocol->ReadCameraSystemSettings() &&
                mRTProtocol->Read3DSettings(any3DSettings) &&
                mRTProtocol->ReadSkeletonSettings(anySkeletonSettings) &&
                mRTProtocol->Read6DOFSettings(any6DOFSettings) &&
                any3DSettings &&
                anySkeletonSettings &&
                any6DOFSettings)
            {
                readSettings = true;

                timecodeFrequency = CalculateTimecodeFrequency(mRTProtocol);

                CreateLiveLinkSubjects();

                SourceStatus = LOCTEXT("SourceStatus_ReadSettings", "Read streaming settings from QTM");
            }
            else
            {
                SourceStatus = FText::FromString(ANSI_TO_TCHAR(mRTProtocol->GetErrorString()));

                FPlatformProcess::Sleep(1.0f);
                continue;
            }
        }

        if (!startedStreaming)
        {
            if (!mRTProtocol->StreamFrames(CRTProtocol::RateAllFrames, 0, 0, nullptr, (CRTProtocol::cComponent3d | CRTProtocol::cComponentSkeleton | CRTProtocol::cComponent6d | CRTProtocol::cComponentTimecode)))
            {
                SourceStatus = FText::FromString(ANSI_TO_TCHAR(mRTProtocol->GetErrorString()));

                FPlatformProcess::Sleep(1.0f);
                continue;
            }
            startedStreaming = true;

            SourceStatus = LOCTEXT("SourceStatus_Receiving", "Receiving data from QTM");
        }

        CRTPacket::EPacketType packetType;
        if (mRTProtocol->ReceiveRTPacket(packetType, false, 0) <= 0)
            continue;

        if (packetType == CRTPacket::PacketEvent)
        {
            // Handle stopping/starting etc.
            CRTPacket* packet = mRTProtocol->GetRTPacket();
            CRTPacket::EEvent qtmEvent;
            if (packet->GetEvent(qtmEvent))
            {
                switch (qtmEvent)
                {
                    case CRTPacket::EventConnectionClosed:
                    case CRTPacket::EventCaptureStopped:
                    case CRTPacket::EventCalibrationStopped:
                    case CRTPacket::EventRTfromFileStopped:
                    case CRTPacket::EventConnected:
                    case CRTPacket::EventCaptureStarted:
                    case CRTPacket::EventCalibrationStarted:
                    case CRTPacket::EventRTfromFileStarted:

                        if (startedStreaming)
                        {
                            DisconnectFromQTM();
                            autoDiscover = false;
                        }

                        ClearSubjects();
                        readSettings = false;
                        startedStreaming = false;
                        break;

                    case CRTPacket::EventQTMShuttingDown:
                        Stop();
                        DisconnectFromQTM();
                        break;
                }
            }
        }
        else if (packetType == CRTPacket::PacketData)
        {
            if (EncounteredSubjects.Num() == 0)
                continue;

            CRTPacket* packet = mRTProtocol->GetRTPacket();

            auto worldTime = FLiveLinkWorldTime(FPlatformTime::Seconds());
            FQualifiedFrameTime sceneTime;

            // There can only be one timecode present
            const auto timecodeCount = packet->GetTimecodeCount();
            if (timecodeCount > 0)
            {
                CRTPacket::ETimecodeType timecodeType;
                if (packet->GetTimecodeType(0, timecodeType))
                {
                    switch (timecodeType)
                    {
                    case CRTPacket::TimecodeSMPTE:
                    {
                        int hours, minutes, seconds, frame;
                        packet->GetTimecodeSMPTE(0, hours, minutes, seconds, frame);
                        ConstructLiveLinkTimeCode(timecodeFrequency, hours, minutes, seconds, frame, sceneTime);
                        break;
                    }
                    case CRTPacket::TimecodeIRIG:
                    {
                        int year, day, hours, minutes, seconds, tenths;
                        packet->GetTimecodeIRIG(0, year, day, hours, minutes, seconds, tenths);
                        ConstructLiveLinkTimeCode(timecodeFrequency, hours, minutes, seconds, 0, sceneTime);
                        break;
                    }
                    case CRTPacket::TimecodeCamerTime:
                    {
                        unsigned __int64 cameraTime;
                        packet->GetTimecodeCameraTime(0, cameraTime);
                        const auto seconds = (cameraTime / 10000000);
                        ConstructLiveLinkTimeCode(timecodeFrequency, seconds, sceneTime);
                        break;
                    }
                    }
                }
            }

            {
                // Skeletons
                const auto skeletonCount = packet->GetSkeletonCount();
                for (unsigned int skeletonIndex = 0; skeletonIndex < skeletonCount; skeletonIndex++)
                {
                    const auto segmentCount = packet->GetSkeletonSegmentCount(skeletonIndex);

                    if (segmentCount == 0)
                    {
                        continue;
                    }

                    const FName skeletonName = mRTProtocol->GetSkeletonName(skeletonIndex);

                    FLiveLinkFrameDataStruct frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkAnimationFrameData::StaticStruct());
                    FLiveLinkAnimationFrameData& subjectFrame = *frameDataStruct.Cast<FLiveLinkAnimationFrameData>();
                    TArray<FTransform>& transforms = subjectFrame.Transforms;
                    transforms.SetNumUninitialized(segmentCount);

                    for (unsigned int segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
                    {
                        CRTProtocol::SSettingsSkeletonSegment settings;
                        mRTProtocol->GetSkeletonSegment(skeletonIndex, segmentIndex, &settings);

                        CRTPacket::SSkeletonSegment segment;
                        packet->GetSkeletonSegment(skeletonIndex, segmentIndex, segment);

                        auto segmentRotation = FQuat(segment.rotationX, -segment.rotationY, -segment.rotationZ, segment.rotationW) * FQuat(settings.rotationX, -settings.rotationY, -settings.rotationZ, settings.rotationW).Inverse();

                        while (settings.parentIndex != -1)
                        {
                            mRTProtocol->GetSkeletonSegment(skeletonIndex, settings.parentIndex, &settings);

                            auto ancestorRotation = FQuat(settings.rotationX, -settings.rotationY, -settings.rotationZ, settings.rotationW);

                            segmentRotation = ancestorRotation * segmentRotation * ancestorRotation.Inverse();
                        }

                        const auto segmentLocation = FVector(-segment.positionX, segment.positionY, segment.positionZ) * positionScalingFactor;
                        const auto segmentScale = FVector(1.0, 1.0, 1.0);

                        transforms[segmentIndex] = FTransform(segmentRotation, segmentLocation, segmentScale);
                    }

                    subjectFrame.WorldTime = worldTime;
                    subjectFrame.MetaData.SceneTime = sceneTime;

                    Client->PushSubjectFrameData_AnyThread({ SourceGuid, skeletonName }, MoveTemp(frameDataStruct));
                }
            }
            {
                // Push rigid body transforms
                const auto rigidBodyCount = packet->Get6DOFBodyCount();
                for (unsigned int rigidBodyIndex = 0; rigidBodyIndex < rigidBodyCount; rigidBodyIndex++)
                {
                    FLiveLinkFrameDataStruct frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkAnimationFrameData::StaticStruct());
                    FLiveLinkAnimationFrameData& subjectFrame = *frameDataStruct.Cast<FLiveLinkAnimationFrameData>();
                    TArray<FTransform>& transforms = subjectFrame.Transforms;
                    transforms.SetNumUninitialized(1);

                    float x, y, z;
                    float R[9];
                    if (packet->Get6DOFBody(rigidBodyIndex, x, y, z, R))
                    {
                        if (isnan(x) || isnan(y) || isnan(z))
                        {
                            continue;
                        }

                        FQuat rotation(FRotationMatrix::MakeFromXY(FVector(R[0], R[1], R[2]), FVector(R[3], R[4], R[5])));
                        FVector position(-x, y, z);
                        position *= positionScalingFactor;
                        FVector scale(1.0, 1.0, 1.0);
                        transforms[0] = FTransform(FQuat(rotation.X, -rotation.Y, -rotation.Z, rotation.W), position, scale);

                        subjectFrame.WorldTime = worldTime;
                        subjectFrame.MetaData.SceneTime = sceneTime;

                        const FName rigidBodyName = mRTProtocol->Get6DOFBodyName(rigidBodyIndex);

                        Client->PushSubjectFrameData_AnyThread({ SourceGuid, rigidBodyName }, MoveTemp(frameDataStruct));
                    }
                }
            }

            {
                // Push marker transforms
                const auto markerCount = packet->Get3DMarkerCount();

                FLiveLinkFrameDataStruct frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkAnimationFrameData::StaticStruct());
                FLiveLinkAnimationFrameData& subjectFrame = *frameDataStruct.Cast<FLiveLinkAnimationFrameData>();
                TArray<FTransform>& transforms = subjectFrame.Transforms;
                transforms.SetNumUninitialized(markerCount);

                for (unsigned int markerIndex = 0; markerIndex < markerCount; markerIndex++)
                {
                    float x, y, z;
                    if (packet->Get3DMarker(markerIndex, x, y, z))
                    {
                        if (isnan(x) || isnan(y) || isnan(z))
                        {
                            continue;
                        }

                        FVector position(-x, y, z);
                        position *= positionScalingFactor;
                        FVector scale(1.0, 1.0, 1.0);
                        transforms[markerIndex] = FTransform(FQuat::Identity, position, scale);
                    }
                }

                subjectFrame.WorldTime = worldTime;
                subjectFrame.MetaData.SceneTime = sceneTime;

                Client->PushSubjectFrameData_AnyThread({ SourceGuid, markersParentName }, MoveTemp(frameDataStruct));
            }

        }
    }

    return 0;
}

void FQTMConnectLiveLinkSource::CreateLiveLinkSubjects()
{
    ClearSubjects();

    {
        // Skeleton
        const auto skeletonCount = mRTProtocol->GetSkeletonCount();
        for (unsigned int skeletonIndex = 0; skeletonIndex < skeletonCount; skeletonIndex++)
        {
            const FName skeletonName = mRTProtocol->GetSkeletonName(skeletonIndex);
            const auto segmentCount = mRTProtocol->GetSkeletonSegmentCount(skeletonIndex);

            TArray<FName> boneNames;
            boneNames.SetNumUninitialized(segmentCount);
            TArray<int32> boneParents;
            boneParents.SetNumUninitialized(segmentCount);

            // Get all names from RT server
            for (unsigned int segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
            {
                CRTProtocol::SSettingsSkeletonSegment segment;
                mRTProtocol->GetSkeletonSegment(skeletonIndex, segmentIndex, &segment);

                boneNames[segmentIndex] = FName(segment.name.c_str());
                boneParents[segmentIndex] = segment.parentIndex;
            }

            FLiveLinkStaticDataStruct subjectDataStruct = FLiveLinkStaticDataStruct(FLiveLinkSkeletonStaticData::StaticStruct());
            FLiveLinkSkeletonStaticData& subjectRefSkeleton = *subjectDataStruct.Cast<FLiveLinkSkeletonStaticData>();
            subjectRefSkeleton.SetBoneNames(boneNames);
            subjectRefSkeleton.SetBoneParents(boneParents);
            Client->PushSubjectStaticData_AnyThread({ SourceGuid, skeletonName }, ULiveLinkAnimationRole::StaticClass(), MoveTemp(subjectDataStruct));

            EncounteredSubjects.Add({ SourceGuid, skeletonName });
        }
    }
    {
        // Rigid body
        const auto rigidBodyCount = mRTProtocol->Get6DOFBodyCount();
        for (unsigned int rigidBodyIndex = 0; rigidBodyIndex < rigidBodyCount; rigidBodyIndex++)
        {
            const FName name = mRTProtocol->Get6DOFBodyName(rigidBodyIndex);

            TArray<FName> boneNames;
            boneNames.SetNumUninitialized(1);
            TArray<int32> boneParents;
            boneParents.SetNumUninitialized(1);

            boneNames[0] = "Bone";
            boneParents[0] = -1;


            FLiveLinkStaticDataStruct subjectDataStruct = FLiveLinkStaticDataStruct(FLiveLinkSkeletonStaticData::StaticStruct());
            FLiveLinkSkeletonStaticData& subjectRefSkeleton = *subjectDataStruct.Cast<FLiveLinkSkeletonStaticData>();
            subjectRefSkeleton.SetBoneNames(boneNames);
            subjectRefSkeleton.SetBoneParents(boneParents);
            Client->PushSubjectStaticData_AnyThread({ SourceGuid, name }, ULiveLinkAnimationRole::StaticClass(), MoveTemp(subjectDataStruct));

            EncounteredSubjects.Add({ SourceGuid, name });
        }
    }
    {
        const auto markerCount = mRTProtocol->Get3DLabeledMarkerCount();

        TArray<FName> markerNames;
        markerNames.SetNumUninitialized(markerCount);
        TArray<int32> markerParents;
        markerParents.SetNumUninitialized(markerCount);

        for (unsigned int markerIndex = 0; markerIndex < markerCount; markerIndex++)
        {
            markerNames[markerIndex] = mRTProtocol->Get3DLabelName(markerIndex);
            markerParents[markerIndex] = -1;
        }

        FLiveLinkStaticDataStruct subjectDataStruct = FLiveLinkStaticDataStruct(FLiveLinkSkeletonStaticData::StaticStruct());
        FLiveLinkSkeletonStaticData& subjectRefSkeleton = *subjectDataStruct.Cast<FLiveLinkSkeletonStaticData>();
        subjectRefSkeleton.SetBoneNames(markerNames);
        subjectRefSkeleton.SetBoneParents(markerParents);

        Client->PushSubjectStaticData_AnyThread({ SourceGuid, markersParentName }, ULiveLinkAnimationRole::StaticClass(), MoveTemp(subjectDataStruct));

        EncounteredSubjects.Add({ SourceGuid, markersParentName });
    }
}

void FQTMConnectLiveLinkSource::ClearSubjects()
{
    // Clear the subject map on stop
    for (const auto &subject : EncounteredSubjects)
    {
        if (Stopping)
            break;
        Client->RemoveSubject_AnyThread(subject);
    }
    EncounteredSubjects.Empty();
}

#pragma optimize("", on)

#undef LOCTEXT_NAMESPACE
