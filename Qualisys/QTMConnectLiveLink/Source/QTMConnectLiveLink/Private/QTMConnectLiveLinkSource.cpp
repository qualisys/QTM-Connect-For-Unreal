// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#include "QTMConnectLiveLinkSource.h"
#include "QTMConnectLiveLinkLog.h"
#include "ILiveLinkClient.h"
#include "LiveLinkTypes.h"
#include "Roles/LiveLinkAnimationRole.h"
#include "Roles/LiveLinkTransformRole.h"
#include "Roles/LiveLinkTransformTypes.h"
#include "Roles/LiveLinkBasicRole.h"
#include "Roles/LiveLinkCameraRole.h"
#include "Roles/LiveLinkCameraTypes.h"
#include "Runtime/Launch/Resources/Version.h"

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
#include "CommonFrameRates.h"

#include <string>

#define LOCTEXT_NAMESPACE "QTMConnectLiveLinkSource"

#define QTM_STREAMING_PORT 22222

const FName markersParentName = "Markers";
 
#pragma optimize("", off)

const std::vector<FString> QTMConnectLiveLinkSettings::STREAMRATES({"All Frames", "Frequency", "Frequency Divisor"});;

QTMConnectLiveLinkSettings QTMConnectLiveLinkSettings::FromString(const FString& settingsString)
{
    QTMConnectLiveLinkSettings settings;
    if (!FParse::Value(*settingsString, TEXT("IpAddress="), settings.IpAddress))
    {
        settings.IpAddress = "127.0.0.1";
    }
    settings.Stream3d = false;
    FString stream3d;
    if (FParse::Value(*settingsString, TEXT("Stream3d="), stream3d))
    {
        settings.Stream3d = stream3d == "true";
    }
    settings.Stream6d = true;
    FString stream6d;
    if (FParse::Value(*settingsString, TEXT("Stream6d="), stream6d))
    {
        settings.Stream6d = stream6d == "true";
    }
    settings.StreamSkeleton = true;
    FString streamSkeleton;
    if (FParse::Value(*settingsString, TEXT("StreamSkeleton="), streamSkeleton))
    {
        settings.StreamSkeleton = streamSkeleton == "true";
    }
    settings.StreamForce = false;
    FString streamForce;
    if (FParse::Value(*settingsString, TEXT("StreamForce="), streamForce))
    {
        settings.StreamForce = streamForce == "true";
    }
    settings.StreamRate = "All Frames";
    FString streamRate;
    if (FParse::Value(*settingsString, TEXT("StreamRate="), streamRate))
    {
        settings.StreamRate = streamRate;
    }
    settings.FrequencyValue = 0;
    FString frequencyValue;
    if (FParse::Value(*settingsString, TEXT("FrequencyValue="), frequencyValue))
    {
        settings.FrequencyValue = FCString::Atoi(*frequencyValue);
    }
    return settings;
}

FString QTMConnectLiveLinkSettings::ToString() const
{
    FString settingsString = FString::Printf(TEXT("IpAddress=\"%s\""), *IpAddress);
    settingsString.Append(FString::Printf(TEXT("Stream3d=\"%s\""), Stream3d ? TEXT("true") : TEXT("false")));
    settingsString.Append(FString::Printf(TEXT("Stream6d=\"%s\""), Stream6d ? TEXT("true") : TEXT("false")));
    settingsString.Append(FString::Printf(TEXT("StreamSkeleton=\"%s\""), StreamSkeleton ? TEXT("true") : TEXT("false")));
    settingsString.Append(FString::Printf(TEXT("StreamForce=\"%s\""), StreamForce ? TEXT("true") : TEXT("false")));
    settingsString.Append(FString::Printf(TEXT("StreamRate=\"%s\""), *StreamRate));
    settingsString.Append(FString::Printf(TEXT("FrequencyValue=\"%d\""), FrequencyValue));
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

#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5) // UE Version >= 5.5
void ConstructLiveLinkTimeCode(int rate, int hours, int minutes, int seconds, int frames, double normalizedSubFrame, FQualifiedFrameTime& timeCode)
{
    timeCode.Rate = FFrameRate(rate, 1);
    FTimecode UnrealTimecode(hours, minutes, seconds, frames, false);

    timeCode.Time = FFrameTime(UnrealTimecode.ToFrameNumber(timeCode.Rate), static_cast<float>(normalizedSubFrame));
}
#endif

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

    rtProtocol->GetGeneralSettings(frequency, captureTime, startOnTrig, trigNo, trigNc, trigSoftware, eProcessingActions, eRtProcessingActions, eReprocessingActions);

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

    int timecodeFrequency = 24;
    int systemFrequency = 24;

    std::string serverAddress(TCHAR_TO_ANSI(*(Settings.IpAddress)));

    while (!Stopping)
    {
        if (mRTProtocol == nullptr)
        {
            mRTProtocol = std::make_shared<CRTProtocol>();
        }
        if (!mRTProtocol->Connected())
        {
            SourceMachineName = FText::FromString(serverAddress.c_str());
            SourceStatus = LOCTEXT("SourceStatus_Connected", "Connecting");            

            if(mRTProtocol->Connect(serverAddress.c_str(), QTM_STREAMING_PORT)) 
            {
                std::string qtmVersion;
                if(mRTProtocol->GetQTMVersion(qtmVersion))
                {
                    UE_LOG(QTMConnectLiveLinkLog, Log, TEXT("Connected to %hs"), qtmVersion.data());
                }

                unsigned int major, minor;
                if(mRTProtocol->GetVersion(major, minor))
                {
                    UE_LOG(QTMConnectLiveLinkLog, Log, TEXT("Using RT Protocol version %d.%d"), major, minor);
                }

                SourceStatus = LOCTEXT("SourceStatus_Connected", "Connected to QTM");
            }
            else
            {
                FPlatformProcess::Sleep(1.0f);
                SourceStatus = FText::FromString(ANSI_TO_TCHAR(mRTProtocol->GetErrorString()));
                continue;
            }
        }

        if (!readSettings)
        {
            bool any3DSettings = false;
            bool anySkeletonSettings = false;
            bool any6DOFSettings = false;
            bool anyForceSettings = false;
            if (mRTProtocol->ReadGeneralSettings() &&
                mRTProtocol->Read3DSettings(any3DSettings) &&
                mRTProtocol->ReadSkeletonSettings(anySkeletonSettings) &&
                mRTProtocol->Read6DOFSettings(any6DOFSettings) &&
                mRTProtocol->ReadForceSettings(anyForceSettings))
            {
                readSettings = true;

                timecodeFrequency = static_cast<int>(std::round(CalculateTimecodeFrequency(mRTProtocol)));
                systemFrequency = mRTProtocol->GetSystemFrequency();

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
            auto components = CRTProtocol::cComponentTimecode;
            if (Settings.Stream3d) 
            {
                components |= CRTProtocol::cComponent3d;
            }
            if (Settings.Stream6d)
            {
                components |= CRTProtocol::cComponent6d;
            }
            if (Settings.StreamSkeleton)
            {
                components |= CRTProtocol::cComponentSkeleton;
            }
            if (Settings.StreamForce)
            {
                components |= CRTProtocol::cComponentForceSingle;
            }
            
            CRTProtocol::EStreamRate streamRate = CRTProtocol::RateAllFrames;
            if (Settings.StreamRate == "Frequency") 
            {
                streamRate = CRTProtocol::RateFrequency;
            }
            else if (Settings.StreamRate == "Frequency Divisor") 
            {
                streamRate = CRTProtocol::RateFrequencyDivisor;
            }

            if (!mRTProtocol->StreamFrames(streamRate, (streamRate != CRTProtocol::RateAllFrames) ? Settings.FrequencyValue : 0, 0, nullptr, components))
            {
                SourceStatus = FText::FromString(ANSI_TO_TCHAR(mRTProtocol->GetErrorString()));

                FPlatformProcess::Sleep(1.0f);
                continue;
            }
            startedStreaming = true;

            SourceStatus = LOCTEXT("SourceStatus_Receiving", "Receiving data from QTM");
        }

        CRTPacket::EPacketType packetType;
        int result = mRTProtocol->ReceiveRTPacket(packetType, false, 1000);
        if (result == 0)
        {
            continue;
        }
        else if (result < 0)
        {
            if (startedStreaming)
            {
                DisconnectFromQTM();
            }

            ClearSubjects();
            readSettings = false;
            startedStreaming = false;
            continue;
        }

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
            if (packet->IsTimeCodeAvailable())
            {
                CRTPacket::ETimecodeType timecodeType;
                if (packet->GetTimecodeType(timecodeType))
                {
                    switch (timecodeType)
                    {
                    case CRTPacket::TimecodeSMPTE:
                    {
                        int hours, minutes, seconds, frame, subFrame;
                        if(systemFrequency >= timecodeFrequency 
                            && timecodeFrequency > 0 
                            && packet->GetTimecodeSMPTE(hours, minutes, seconds, frame, subFrame) //return true for RTProtocol >= 1.27 only
                        ) 
                        {
                            #if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5) // UE Version >= 5.5
                                const auto normalizedSubFrame = CRTProtocol::SMPTENormalizedSubFrame(systemFrequency, timecodeFrequency, subFrame);
                                ConstructLiveLinkTimeCode(timecodeFrequency, hours, minutes, seconds, frame, normalizedSubFrame, sceneTime);
                            #else
                                const auto relativeFrequency = systemFrequency / timecodeFrequency;
                                const auto highSpeedFrame = frame * relativeFrequency + subFrame;
                                ConstructLiveLinkTimeCode(systemFrequency, hours, minutes, seconds, highSpeedFrame, sceneTime);    
                            #endif
                        }
                        else if(packet->GetTimecodeSMPTE(hours, minutes, seconds, frame))
                        {
                            //Legacy behaviour
                            ConstructLiveLinkTimeCode(timecodeFrequency, hours, minutes, seconds, frame, sceneTime);
                        }

                        break;
                    }
                    case CRTPacket::TimecodeIRIG:
                    {
                        int year, day, hours, minutes, seconds, tenths;
                        packet->GetTimecodeIRIG(year, day, hours, minutes, seconds, tenths);
                        ConstructLiveLinkTimeCode(timecodeFrequency, hours, minutes, seconds, 0, sceneTime);
                        break;
                    }
                    case CRTPacket::TimecodeCamerTime:
                    {
                        uint64 cameraTime; //on windows platforms uint64 resolves to unsigned long long which is synonymous with unsigned __int64
                        packet->GetTimecodeCameraTime(cameraTime);
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
                        
                        auto segmentRotation = FQuat(-segment.rotationX, segment.rotationY, -segment.rotationZ, segment.rotationW) * FQuat(-settings.rotationX, settings.rotationY, -settings.rotationZ, settings.rotationW).Inverse();

                        while (settings.parentIndex != -1)
                        {
                            mRTProtocol->GetSkeletonSegment(skeletonIndex, settings.parentIndex, &settings);

                            auto ancestorRotation = FQuat(-settings.rotationX, settings.rotationY, -settings.rotationZ, settings.rotationW);

                            segmentRotation = ancestorRotation * segmentRotation * ancestorRotation.Inverse();
                        }

                        const auto segmentLocation = FVector(segment.positionX, -segment.positionY, segment.positionZ) * positionScalingFactor;

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
                    const FName rigidBodyName = mRTProtocol->Get6DOFBodyName(rigidBodyIndex);
                    FLiveLinkFrameDataStruct frameDataStruct;
                    if (rigidBodyName.ToString().StartsWith("cam_", ESearchCase::Type::IgnoreCase))
                    {
                        frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkCameraFrameData::StaticStruct());
                    }
                    else
                    {
                        frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkTransformFrameData::StaticStruct());
                    }
                    FLiveLinkTransformFrameData& subjectFrame = *frameDataStruct.Cast<FLiveLinkTransformFrameData>();
                    float x, y, z;
                    float R[9];
                    if (packet->Get6DOFBody(rigidBodyIndex, x, y, z, R))
                    {
                        if (isnan(x) || isnan(y) || isnan(z))
                        {
                            continue;
                        }

                        FQuat rotation(FRotationMatrix::MakeFromXY(FVector(R[0], R[1], R[2]), FVector(R[3], R[4], R[5])));
                        FVector position(x, -y, z);
                        position *= positionScalingFactor;
                        FVector scale(1.0, 1.0, 1.0);
                        subjectFrame.Transform = FTransform(FQuat(-rotation.X, rotation.Y, -rotation.Z, rotation.W), position, scale);

                        subjectFrame.WorldTime = worldTime;
                        subjectFrame.MetaData.SceneTime = sceneTime;

                        Client->PushSubjectFrameData_AnyThread({ SourceGuid, rigidBodyName }, MoveTemp(frameDataStruct));
                    }
                }
            }

            {
                // Push marker transforms
                const auto markerCount = packet->Get3DMarkerCount();

                if (markerCount > 0)
                {
                    for (unsigned int markerIndex = 0; markerIndex < markerCount; markerIndex++)
                    {
                        FLiveLinkFrameDataStruct frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkTransformFrameData::StaticStruct());
                        FLiveLinkTransformFrameData& subjectFrame = *frameDataStruct.Cast<FLiveLinkTransformFrameData>();

                        float x, y, z;
                        if (packet->Get3DMarker(markerIndex, x, y, z))
                        {
                            if (isnan(x) || isnan(y) || isnan(z))
                            {
                                continue;
                            }

                            FVector position(x, -y, z);
                            position *= positionScalingFactor;
                            FVector scale(1.0, 1.0, 1.0);
                            subjectFrame.Transform = FTransform(FQuat::Identity, position, scale);

                            subjectFrame.WorldTime = worldTime;
                            subjectFrame.MetaData.SceneTime = sceneTime;
                            
                            const FName name = mRTProtocol->Get3DLabelName(markerIndex);

                            Client->PushSubjectFrameData_AnyThread({ SourceGuid, name }, MoveTemp(frameDataStruct));
                        }
                    }
                }
            }

            {
                const auto forcePlateCount = packet->GetForceSinglePlateCount();

                CRTPacket::SForce force;
                for (auto forcePlateIndex = 0u; forcePlateIndex < forcePlateCount; forcePlateIndex++)
                {
                    const auto forcePlateId = packet->GetForceSinglePlateId(forcePlateIndex);
                    const auto forceName = FName(mForceIdToName[forcePlateId]);

                    FLiveLinkFrameDataStruct frameDataStruct = FLiveLinkFrameDataStruct(FLiveLinkBaseFrameData::StaticStruct());
                    FLiveLinkBaseFrameData& subjectFrame = *frameDataStruct.Cast<FLiveLinkBaseFrameData>();
                    if (packet->GetForceSingleData(forcePlateIndex, force))
                    {
                        subjectFrame.PropertyValues.Add(force.fForceX);
                        subjectFrame.PropertyValues.Add(force.fForceY);
                        subjectFrame.PropertyValues.Add(force.fForceZ);
                        subjectFrame.PropertyValues.Add(force.fMomentX);
                        subjectFrame.PropertyValues.Add(force.fMomentY);
                        subjectFrame.PropertyValues.Add(force.fMomentZ);
                        subjectFrame.PropertyValues.Add(force.fApplicationPointX);
                        subjectFrame.PropertyValues.Add(force.fApplicationPointY);
                        subjectFrame.PropertyValues.Add(force.fApplicationPointZ);
                    }

                    subjectFrame.WorldTime = worldTime;
                    subjectFrame.MetaData.SceneTime = sceneTime;

                    Client->PushSubjectFrameData_AnyThread({ SourceGuid, forceName }, MoveTemp(frameDataStruct));
                }
            }
        }
    }

    return 0;
}

void FQTMConnectLiveLinkSource::CreateLiveLinkSubjects()
{
    ClearSubjects();

    if (Settings.StreamSkeleton)
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
    if (Settings.Stream6d)
    {
        // Rigid body
        const auto rigidBodyCount = mRTProtocol->Get6DOFBodyCount();
        for (unsigned int rigidBodyIndex = 0; rigidBodyIndex < rigidBodyCount; rigidBodyIndex++)
        {
            const FName name = mRTProtocol->Get6DOFBodyName(rigidBodyIndex);
            if (name.ToString().StartsWith("cam_", ESearchCase::Type::IgnoreCase))
            {
                FLiveLinkStaticDataStruct subjectDataStruct = FLiveLinkStaticDataStruct(FLiveLinkCameraStaticData::StaticStruct());
                Client->PushSubjectStaticData_AnyThread({ SourceGuid, name }, ULiveLinkCameraRole::StaticClass(), MoveTemp(subjectDataStruct));
            }
            else
            {
                FLiveLinkStaticDataStruct subjectDataStruct = FLiveLinkStaticDataStruct(FLiveLinkTransformStaticData::StaticStruct());
                Client->PushSubjectStaticData_AnyThread({ SourceGuid, name }, ULiveLinkTransformRole::StaticClass(), MoveTemp(subjectDataStruct));
            }
            EncounteredSubjects.Add({ SourceGuid, name });
        }
    }
    if (Settings.Stream3d)
    {
        const auto markerCount = mRTProtocol->Get3DLabeledMarkerCount();

        for (unsigned int markerIndex = 0; markerIndex < markerCount; markerIndex++)
        {
            const FName name = mRTProtocol->Get3DLabelName(markerIndex);

            FLiveLinkStaticDataStruct subjectDataStruct = FLiveLinkStaticDataStruct(FLiveLinkTransformStaticData::StaticStruct());
            Client->PushSubjectStaticData_AnyThread({ SourceGuid, name }, ULiveLinkTransformRole::StaticClass(), MoveTemp(subjectDataStruct));

            EncounteredSubjects.Add({ SourceGuid, name });
        }
    }
    if (Settings.StreamForce)
    {
        const auto forcePlateCount = mRTProtocol->GetForcePlateCount();

        for (unsigned int forcePlateIndex = 0; forcePlateIndex < forcePlateCount; forcePlateIndex++)
        {
            unsigned int        nPlateID, nAnalogDeviceID, nFrequency;
            float               fLength, fWidth;
            char* pType;
            char* pName;
            mRTProtocol->GetForcePlate(forcePlateIndex, nPlateID, nAnalogDeviceID, nFrequency, pType, pName, fLength, fWidth);

            mForceIdToName[nPlateID] = pName;
            const auto name = FName(pName);

            FLiveLinkStaticDataStruct subjectDataStruct = FLiveLinkStaticDataStruct(FLiveLinkBaseStaticData::StaticStruct());
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Force X"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Force Y"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Force Z"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Moment X"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Moment Y"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Moment Z"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Application Point X"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Application Point Y"));
            subjectDataStruct.GetBaseData()->PropertyNames.Add(FName("Application Point Z"));
            Client->PushSubjectStaticData_AnyThread({ SourceGuid, name }, ULiveLinkBasicRole::StaticClass(), MoveTemp(subjectDataStruct));
            EncounteredSubjects.Add({ SourceGuid, name });
        }
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
    mForceIdToName.clear();
}

#pragma optimize("", on)

#undef LOCTEXT_NAMESPACE
