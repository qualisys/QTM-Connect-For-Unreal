// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
//
#include "QTMConnectLiveLinkSource.h"
#include "ILiveLinkClient.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#include "RTProtocol.h"
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include <string>

#define LOCTEXT_NAMESPACE "QTMConnectLiveLinkSource"

#define QTM_STREAMING_PORT 22222

#pragma optimize("", off)

FQTMConnectLiveLinkSource::FQTMConnectLiveLinkSource(const QTMConnectLiveLinkSettings& settings)
    : Settings(settings)
    , Stopping(false)
    , Thread(nullptr)
{
    SourceType = LOCTEXT("QTMConnectLiveLinkSourceType", "QTM Connect LiveLink");
    SourceStatus = LOCTEXT("SourceStatus_NotConnected", "Not connected");
    FString machineName(settings.IpAddress + ":" + FString::FromInt(settings.Port));
    SourceMachineName = FText::FromString(machineName);
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
}

void FQTMConnectLiveLinkSource::ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid)
{
    Client = InClient;
    SourceGuid = InSourceGuid;

    Start();
}


bool FQTMConnectLiveLinkSource::IsSourceStillValid()
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

    if (mRTProtocol)
    {
        mRTProtocol->StreamFramesStop();
        mRTProtocol->Disconnect();
        mRTProtocol = nullptr;
    }

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

uint32 FQTMConnectLiveLinkSource::Run()
{
    // mm to m to world scale
    const float positionScalingFactor = QtmToUEScalingFactor();

    bool readSettings = false;
    bool startedStreaming = false;

    unsigned short udpPort = Settings.Port;
    const std::string serverAddr(TCHAR_TO_ANSI(*(Settings.IpAddress)));

    while (!Stopping)
    {
        if (mRTProtocol == nullptr)
        {
            mRTProtocol = std::make_shared<CRTProtocol>();
        }
        if (!mRTProtocol->Connected())
        {
            if (!mRTProtocol->Connect(serverAddr.c_str(), QTM_STREAMING_PORT, &udpPort))
            {
                SourceStatus = FText::FromString(ANSI_TO_TCHAR(mRTProtocol->GetErrorString()));

                FPlatformProcess::Sleep(1.0f);
                continue;
            }

            SourceStatus = LOCTEXT("SourceStatus_Connected", "Connected to QTM");
        }

        if (!readSettings)
        {
            bool anyData;
            if (!mRTProtocol->ReadSkeletonSettings(anyData) || !mRTProtocol->Read6DOFSettings(anyData))
            {
                SourceStatus = FText::FromString(ANSI_TO_TCHAR(mRTProtocol->GetErrorString()));

                FPlatformProcess::Sleep(1.0f);
                continue;
            }
            readSettings = true;

            CreateLiveLinkSubjects();

            SourceStatus = LOCTEXT("SourceStatus_ReadSettings", "Read streaming settings from QTM");
        }

        if (!startedStreaming)
        {
            if (!mRTProtocol->StreamFrames(CRTProtocol::RateAllFrames, 0, udpPort, nullptr, (CRTProtocol::cComponentSkeleton | CRTProtocol::cComponent6d)))
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
                        ClearSubjects();
                        readSettings = false;
                        startedStreaming = false;
                        break;

                    case CRTPacket::EventQTMShuttingDown:
                        Stop();
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

            const auto skeletonCount = packet->GetSkeletonCount();
            for (unsigned int skeletonIndex = 0; skeletonIndex < skeletonCount; skeletonIndex++)
            {
                const auto segmentCount = packet->GetSkeletonSegmentCount(skeletonIndex);

                if (segmentCount == 0)
                {
                    continue;
                }

                FLiveLinkFrameData subjectFrame;
                TArray<FTransform>& transforms = subjectFrame.Transforms;
                transforms.SetNumUninitialized(segmentCount);

                for (unsigned int segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
                {
                    CRTPacket::SSkeletonSegment segment;
                    packet->GetSkeletonSegment(skeletonIndex, segmentIndex, segment);

                    const auto segmentRotation = FQuat(segment.rotationX, -segment.rotationY, -segment.rotationZ, segment.rotationW);
                    const auto segmentLocation = FVector(-segment.positionX, segment.positionY, segment.positionZ) * positionScalingFactor;
                    const auto segmentScale = FVector(1.0, 1.0, 1.0);

                    transforms[segmentIndex] = FTransform(segmentRotation, segmentLocation, segmentScale);
                }

                subjectFrame.WorldTime = worldTime;

                const FName skeletonName = mRTProtocol->GetSkeletonName(skeletonIndex);

                Client->PushSubjectData(SourceGuid, skeletonName, subjectFrame);
            }
            const auto rigidBodyCount = packet->Get6DOFBodyCount();
            for (unsigned int rigidBodyIndex = 0; rigidBodyIndex < rigidBodyCount; rigidBodyIndex++)
            {
                FLiveLinkFrameData subjectFrame;
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

                    const FName rigidBodyName = mRTProtocol->Get6DOFBodyName(rigidBodyIndex);

                    Client->PushSubjectData(SourceGuid, rigidBodyName, subjectFrame);
                }           
            }

            // TODO::: Also push something to ActiveEditorCamera?
        }
    }

    return 0;
}

void FQTMConnectLiveLinkSource::CreateLiveLinkSubjects()
{
    ClearSubjects();

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

        FLiveLinkRefSkeleton subjectRefSkeleton;
        subjectRefSkeleton.SetBoneNames(boneNames);
        subjectRefSkeleton.SetBoneParents(boneParents);

        Client->PushSubjectSkeleton(SourceGuid, skeletonName, subjectRefSkeleton);

        EncounteredSubjects.Add(skeletonName);
    }
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

        FLiveLinkRefSkeleton subjectRefSkeleton;
        subjectRefSkeleton.SetBoneNames(boneNames);
        subjectRefSkeleton.SetBoneParents(boneParents);

        Client->PushSubjectSkeleton(SourceGuid, name, subjectRefSkeleton);

        EncounteredSubjects.Add(name);
    }
}

void FQTMConnectLiveLinkSource::ClearSubjects()
{
    // Clear the subject map on stop
    for (const auto &subject : EncounteredSubjects)
    {
        Client->ClearSubject(subject);
    }
    EncounteredSubjects.Empty();
}

#pragma optimize("", on)

#undef LOCTEXT_NAMESPACE
