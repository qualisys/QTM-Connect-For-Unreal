// QTM Connect For Unreal. Copyright 2018 Qualisys
//
#include "CoreMinimal.h"

#include "QualisysClient.h"
#include "QTMConnect.h"
#include "QualisysRigidBody.h"

#include <EngineUtils.h>

#include "AllowWindowsPlatformTypes.h"
#include "AllowWindowsPlatformAtomics.h"
#include "RTProtocol.h"
#include "RTPacket.h"
#include "HideWindowsPlatformAtomics.h"
#include "HideWindowsPlatformTypes.h"

#define LOCTEXT_NAMESPACE "QTMConnect"

#define QTM_STREAM_PORT             22222
#define QTM_STREAM_MAJOR_VERSION    1
#define QTM_STREAM_MINOR_VERSION    13

AQualisysClient::AQualisysClient(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    mRTProtocol(nullptr),
    mLastFrameNumber(-1),
    IPAddressToQTMServer("127.0.0.1"),
    UdpPort(6789),
    StreamRate(0)
{
    RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootSceneComponent"));

#if WITH_EDITORONLY_DATA
    RootComponent->bVisualizeComponent = true;
#endif

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.TickGroup = TG_PostPhysics;
}


bool AQualisysClient::GetRigidBodyPose(FString RigidBody, FQualisysRigidBodyPose& RigidBodyPose)
{
    if (GetRigidBodyPoseUntransformedByClient(RigidBody, RigidBodyPose))
    {
        const FTransform rigidBodyTransform(RigidBodyPose.Orientation, RigidBodyPose.Position);

        const FTransform rigidBodyTransformedByClient = rigidBodyTransform * GetTransform();
        RigidBodyPose.Position = rigidBodyTransformedByClient.GetLocation();
        RigidBodyPose.Orientation = rigidBodyTransformedByClient.GetRotation();
        return true;
    }
    return false;
}

AQualisysClient* AQualisysClient::FindQualisysClient(UWorld* World)
{
    AQualisysClient* firstClientInWorld = nullptr;

    int numberOfQualisysClientsInWorld = 0;
    for (TActorIterator<AQualisysClient> QualisysClientIterator(World); QualisysClientIterator; ++QualisysClientIterator, ++numberOfQualisysClientsInWorld)
    {
        if (numberOfQualisysClientsInWorld == 0)
        {
            firstClientInWorld = *QualisysClientIterator;
        }
    }
    if (numberOfQualisysClientsInWorld == 0)
    {
        GLog->Logf(TEXT("AQualisysClient::FindQualisysClient: No Qualisys client actor available in the World."));
    }
    else if (numberOfQualisysClientsInWorld > 1)
    {
        GLog->Logf(TEXT("AQualisysClient::FindQualisysClient: Multiple Qualisys client actors found. Using first %s."), *firstClientInWorld->GetName());
    }
    return firstClientInWorld;
}

void AQualisysClient::PreInitializeComponents()
{
    InitializeQualisysClient();

    Super::PreInitializeComponents();
}

void AQualisysClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    ShutdownQualisysClient();
}

void AQualisysClient::InitializeQualisysClient()
{
    check(IQTMConnectPlugin::IsAvailable());

    check(mRTProtocol == nullptr);
    mRTProtocol = IQTMConnectPlugin::Get().CreateRTObject();
    check(mRTProtocol != nullptr);

    // If one want to automatically find the first available QTM instance streaming data then we can discover it.
    //if (mRTProtocol->DiscoverRTServer(0, false))
    //{
    //    if (discoverResponses >= 1)
    //    {
    //        char message[256];
    //        unsigned int addr;
    //        unsigned short basePort;
    //        if (mRTProtocol->GetDiscoverResponse(0, addr, basePort, message, sizeof(message)))
    //        {
    //            char serverAddr[40];
    //            sprintf_s(serverAddr, "%d.%d.%d.%d", 0xff & addr, 0xff & (addr >> 8), 0xff & (addr >> 16), 0xff & (addr >> 24));
    //            IPAddressToQTMServer = serverAddr;
    //        }
    //    }
    //}

    const std::string serverAddr(TCHAR_TO_ANSI(*IPAddressToQTMServer));
    unsigned short sUdpPort = UdpPort;
    auto connected = mRTProtocol->Connect(serverAddr.c_str(), QTM_STREAM_PORT, &sUdpPort, QTM_STREAM_MAJOR_VERSION, QTM_STREAM_MINOR_VERSION);
    if (!connected)
    {
        GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: Connection to QTM failed: %s"), serverAddr.c_str());
        ShutdownQualisysClient();
        return;
    }

    bool anyData;
    auto settingsAvailable = mRTProtocol->Read3DSettings(anyData);
    if (!settingsAvailable)
    {
        GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: Reading 3D settings failed"));
        ShutdownQualisysClient();
        return;
    }
    settingsAvailable = mRTProtocol->Read6DOFSettings(anyData);
    if (!settingsAvailable)
    {
        GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: Reading 6DOF settings failed"));
        ShutdownQualisysClient();
        return;
    }

    const auto streamRateType = (StreamRate <= 0) ? CRTProtocol::RateAllFrames : CRTProtocol::RateFrequency;
    const auto componentsToStream = CRTProtocol::cComponent6d | CRTProtocol::cComponent3d;
    auto streaming = mRTProtocol->StreamFrames(streamRateType, StreamRate, UdpPort, nullptr, componentsToStream, nullptr);
    if (!streaming)
    {
        GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: StreamFrames failed"));
        ShutdownQualisysClient();
        return;
    }
}

void AQualisysClient::ShutdownQualisysClient()
{
    if (mRTProtocol != nullptr)
    {
        mUpdateLock.Lock();

        mRTProtocol->StreamFramesStop();
        mRTProtocol->Disconnect();

        check(IQTMConnectPlugin::IsAvailable());
        IQTMConnectPlugin::Get().DestroyRTObject(mRTProtocol);

        mRTProtocol = nullptr;

        mUpdateLock.Unlock();
    }
}

void AQualisysClient::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
    Super::TickActor(DeltaTime, TickType, ThisTickFunction);

    if (mRTProtocol == nullptr)
        return;

    CRTPacket::EPacketType packetType;
    auto ret = mRTProtocol->ReceiveRTPacket(packetType, false);
    if (ret <= 0)
        return;

    auto rtPacket = mRTProtocol->GetRTPacket();
    if (packetType == CRTPacket::PacketEvent)
    {
        CRTPacket::EEvent qtmEvent;
        rtPacket->GetEvent(qtmEvent);
        if (qtmEvent == CRTPacket::EventRTfromFileStarted ||
            qtmEvent == CRTPacket::EventConnected ||
            qtmEvent == CRTPacket::EventCaptureStarted ||
            qtmEvent == CRTPacket::EventCalibrationStarted)
        {
            // ReadXML settings again and reset any stored states
            bool anyData;
            mRTProtocol->Read3DSettings(anyData);
            mRTProtocol->Read6DOFSettings(anyData);
            if (mUpdateLock.TryLock())
            {
                //mMarkerPositions.Empty();
                mRigidBodyPoses.Empty();
            }
        }
    }
    else if (packetType == CRTPacket::PacketData)
    {
        const auto frameNumber = rtPacket->GetFrameNumber();
        if (frameNumber == mLastFrameNumber)
            return;

        // mm to m to world scale
        const float positionScalingFactor = 0.001 * GetWorld()->GetWorldSettings()->WorldToMeters;

        mLastFrameNumber = frameNumber;

        float x, y, z;
        float rotationMatrix[9];

        //const auto markers = rtPacket->Get3DMarkerCount();
        //for (uint32_t m = 0; m < markers; m++)
        //{
        //    auto markerName = mRTProtocol->Get3DLabelName(m);
        //    if (markerName == nullptr)
        //        continue;

        //    if (rtPacket->Get3DMarker(m, x, y, z))
        //    {
        //        FQualisysMarker marker;
        //        // mm to m to world scale
        //        // Also swap x, y positions 
        //        
        //        marker.Position.X = y / 1000.0 * positionScalingFactor;
        //        marker.Position.Y = x / 1000.0 * positionScalingFactor;
        //        marker.Position.Z = z / 1000.0 * positionScalingFactor;
        //        if (mUpdateLock.TryLock())
        //        {
        //            mMarkerPositions.Emplace(markerName, marker);
        //            mUpdateLock.Unlock();
        //        }
        //    }
        //}

        const auto bodies = rtPacket->Get6DOFBodyCount();
        for (uint32_t b = 0; b < bodies; b++)
        {
            auto bodyName = mRTProtocol->Get6DOFBodyName(b);
            if (bodyName == nullptr)
                continue;

            if (rtPacket->Get6DOFBody(b, x, y, z, rotationMatrix))
            {
                FQualisysRigidBodyPose rigidBodyPose;

                // TODO:
                // Handle QTMs all possible coordinate system settings
                // and convert orientation correctly to unreal.

                rigidBodyPose.Position.X = y * positionScalingFactor;
                rigidBodyPose.Position.Y = x * positionScalingFactor;
                rigidBodyPose.Position.Z = z * positionScalingFactor;

                FMatrix uRotationMatrix;
                uRotationMatrix.SetIdentity();
                uRotationMatrix.M[0][0] = rotationMatrix[0];
                uRotationMatrix.M[0][1] = rotationMatrix[3];
                uRotationMatrix.M[0][2] = rotationMatrix[6];
                uRotationMatrix.M[1][0] = rotationMatrix[1];
                uRotationMatrix.M[1][1] = rotationMatrix[4];
                uRotationMatrix.M[1][2] = rotationMatrix[7];
                uRotationMatrix.M[2][0] = rotationMatrix[2];
                uRotationMatrix.M[2][1] = rotationMatrix[5];
                uRotationMatrix.M[2][2] = rotationMatrix[8];
                rigidBodyPose.Orientation = uRotationMatrix.ToQuat();

                FString rigidBodyName(bodyName);
                if (mUpdateLock.TryLock())
                {
                    mRigidBodyPoses.Emplace(rigidBodyName.ToLower(), rigidBodyPose);
                    mUpdateLock.Unlock();
                }
            }
        }
    }
}

bool AQualisysClient::GetRigidBodyPoseUntransformedByClient(FString rigidBodyName, FQualisysRigidBodyPose& rigidBodyPose)
{
    auto result = false;
    mUpdateLock.Lock();
    if (FQualisysRigidBodyPose* pose = mRigidBodyPoses.Find(rigidBodyName.ToLower()))
    {
        rigidBodyPose = *pose;
        result = true;
    }
    mUpdateLock.Unlock();
    return result;
}

#undef LOCTEXT_NAMESPACE
