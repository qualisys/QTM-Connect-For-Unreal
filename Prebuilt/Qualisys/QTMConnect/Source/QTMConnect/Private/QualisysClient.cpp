// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
//
#include "QualisysClient.h"

#include "QTMConnect.h"
#include "QualisysRigidBody.h"

#include <EngineUtils.h>
#include <DrawDebugHelpers.h>

#include <Windows/AllowWindowsPlatformTypes.h>
#include <Windows/AllowWindowsPlatformAtomics.h>
#include "RTProtocol.h"
#include "RTPacket.h"
#include <Windows/HideWindowsPlatformAtomics.h>
#include <Windows/HideWindowsPlatformTypes.h>

#include <numeric>
#include <cmath>

#define LOCTEXT_NAMESPACE "QTMConnect"

#define QTM_STREAMING_PORT 22222

#pragma optimize("", off)

AQualisysClient::AQualisysClient(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer),
    AutoDiscoverQTMServer(true),
    IPAddressToQTMServer("127.0.0.1"),
    UdpPort(6789),
    StreamRate(0),
    DebugDrawingRigidBodies(false),
    DebugDrawingTrajectories(false),
    mRtProtocol(nullptr)
{
    RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootSceneComponent"));

#if WITH_EDITORONLY_DATA
    RootComponent->bVisualizeComponent = true;
#endif

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bTickEvenWhenPaused = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.TickGroup = TG_PrePhysics;
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

    if (mRtProtocol == nullptr)
    {
        mRtProtocol = IQTMConnectPlugin::Get().CreateRTObject();

        if (AutoDiscoverQTMServer)
        {
            // If one want to automatically find the first available QTM instance streaming data then we can discover it.
            if (mRtProtocol->DiscoverRTServer(0, false))
            {
                const auto discoverResponses = mRtProtocol->GetNumberOfDiscoverResponses();
                if (discoverResponses >= 1)
                {
                    char message[256];
                    unsigned int addr;
                    unsigned short basePort;
                    if (mRtProtocol->GetDiscoverResponse(0, addr, basePort, message, sizeof(message)))
                    {
                        char serverAddr[40];
                        sprintf_s(serverAddr, "%d.%d.%d.%d", 0xff & addr, 0xff & (addr >> 8), 0xff & (addr >> 16), 0xff & (addr >> 24));
                        IPAddressToQTMServer = serverAddr;
                    }
                }
            }
        }

        const std::string serverAddr(TCHAR_TO_ANSI(*IPAddressToQTMServer));
        unsigned short sUdpPort = UdpPort;
        auto connected = mRtProtocol->Connect(serverAddr.c_str(), QTM_STREAMING_PORT, &sUdpPort);
        if (!connected)
        {
            GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: Connection to QTM failed: %s"), serverAddr.c_str());
            ShutdownQualisysClient();
            return;
        }
    }

    unsigned int componentsToStream = 0;

    bool anyData;
    auto threeDSettingsAvailable = mRtProtocol->Read3DSettings(anyData);
    if (threeDSettingsAvailable && anyData)
    {
        componentsToStream |= CRTProtocol::cComponent3d;
    }
    else
    {
        GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: Reading 3D settings failed"));
        ShutdownQualisysClient();
        return;
    }
    auto sixDofSettingsAvailable = mRtProtocol->Read6DOFSettings(anyData);
    if (sixDofSettingsAvailable && anyData)
    {
        componentsToStream |= CRTProtocol::cComponent6d;
    }
    else
    {
        GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: Reading 6DOF settings failed"));
        ShutdownQualisysClient();
        return;
    }

    const auto streamRateType = (StreamRate <= 0) ? CRTProtocol::RateAllFrames : CRTProtocol::RateFrequency;
    auto streaming = mRtProtocol->StreamFrames(streamRateType, StreamRate, UdpPort, nullptr, componentsToStream);
    if (!streaming)
    {
        GLog->Logf(TEXT("AQualisysClient::InitializeQualisysClient: StreamFrames failed"));
        ShutdownQualisysClient();
        return;
    }

    SetActorTickInterval(0.01);
}

void AQualisysClient::ShutdownQualisysClient()
{
    if (mRtProtocol != nullptr)
    {
        CAutoLock lock(&mUpdateLock);

        mRtProtocol->StreamFramesStop();
        mRtProtocol->Disconnect();

        check(IQTMConnectPlugin::IsAvailable());
        IQTMConnectPlugin::Get().DestroyRTObject(mRtProtocol);

        mRtProtocol = nullptr;
    }
}

static FQuat MatrixToQuaternion(const float matrix[9])
{
    float quat[4];
    float trace = matrix[0 * 3 + 0] + matrix[1 * 3 + 1] + matrix[2 * 3 + 2];
    float root;
    if (trace > 0)
    {
        root = std::sqrt(trace + 1.0);  // 2w
        quat[3] = 0.5 * root;
        root = 0.5 / root;  // 1/(4w)
        quat[0] = (matrix[2 * 3 + 1] - matrix[1 * 3 + 2]) * root;
        quat[1] = (matrix[0 * 3 + 2] - matrix[2 * 3 + 0]) * root;
        quat[2] = (matrix[1 * 3 + 0] - matrix[0 * 3 + 1]) * root;
    }
    else
    {
        int s_Next[3] = { 1, 2, 0 };
        int i = 0;
        if (matrix[1 * 3 + 1] > matrix[0 * 3 + 0])
            i = 1;
        if (matrix[2 * 3 + 2] > matrix[i * 3 + i])
            i = 2;
        int j = s_Next[i];
        int k = s_Next[j];
        root = std::sqrt(matrix[i * 3 + i] - matrix[j * 3 + j] - matrix[k * 3 + k] + 1.0);
        quat[i] = 0.5 * root;
        root = 0.5 / root;
        quat[3] = (matrix[k * 3 + j] - matrix[j * 3 + k]) * root;
        quat[j] = (matrix[j * 3 + i] + matrix[i * 3 + j]) * root;
        quat[k] = (matrix[k * 3 + i] + matrix[i * 3 + k]) * root;
    }
    const float innerProduct = std::inner_product(quat, quat + 4, quat, 0.0);
    const float magnitude = std::sqrt(innerProduct);

    auto q = FQuat(quat[0], quat[1], quat[2], quat[3]);
    q /= magnitude;
    return q;
}

void AQualisysClient::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
    Super::TickActor(DeltaTime, TickType, ThisTickFunction);

    if (mRtProtocol == nullptr || !mRtProtocol->Connected())
        return;

    CRTPacket::EPacketType packetType;
    auto ret = mRtProtocol->ReceiveRTPacket(packetType, false, 0);
    if (ret <= 0)
        return;

    auto rtPacket = mRtProtocol->GetRTPacket();
    if (packetType == CRTPacket::PacketEvent)
    {
        HandleQtmEvents(rtPacket);
    }
    else if (packetType == CRTPacket::PacketData)
    {
        HandleQtmData(rtPacket);

        if (DebugDrawingRigidBodies)
        {
            for (auto rigidBody : mRigidBodies)
            {
                FColor color;
                ConvertQtmColorToUE(mRtProtocol->Get6DOFBodyColor(rigidBody.Value.Index), color);
                DrawDebugSolidBox(GetWorld(), FBox(FVector(-5, -5, -5), FVector(5, 5, 5)), color, FTransform(rigidBody.Value.Orientation, rigidBody.Value.Position));
                DrawDebugCoordinateSystem(GetWorld(), rigidBody.Value.Position, rigidBody.Value.Orientation.Rotator(), 20, false, 0, 0, 2);
            }
        }
        if (DebugDrawingTrajectories)
        {
            for (auto trajectory : mTrajectories)
            {
                FColor color;
                ConvertQtmColorToUE(mRtProtocol->Get3DLabelColor(trajectory.Value.Index), color);
                DrawDebugSphere(GetWorld(), trajectory.Value.Position, 4, 20, color, false, -1, 0, 1);
            }
        }
    }
}

void AQualisysClient::ConvertQtmColorToUE(unsigned int qtmColor, FColor &color)
{
    color.R = (qtmColor) & 0xFF;
    color.G = (qtmColor >> 8) & 0xFF;
    color.B = (qtmColor >> 16) & 0xFF;
    color.A = 255;
}

void AQualisysClient::HandleQtmData(CRTPacket * rtPacket)
{
    // mm to m to world scale
    const float positionScalingFactor = 0.001 * GetWorld()->GetWorldSettings()->WorldToMeters;

    if (mUpdateLock.TryLock())
    {
        float x, y, z;
        float rotationMatrix[9];

        const auto trajectoryCount = rtPacket->Get3DMarkerCount();
        for (unsigned int trajectoryIndex = 0; trajectoryIndex < trajectoryCount; trajectoryIndex++)
        {
            auto trajectoryName = mRtProtocol->Get3DLabelName(trajectoryIndex);
            if (trajectoryName == nullptr)
                continue;

            if (rtPacket->Get3DMarker(trajectoryIndex, x, y, z))
            {
                // mm to m to world scale and swap x, y positions 
                FQualisysTrajectoryInfo trajectory;
                trajectory.Position.X = y * positionScalingFactor;
                trajectory.Position.Y = x * positionScalingFactor;
                trajectory.Position.Z = z * positionScalingFactor;
                trajectory.Index = trajectoryIndex;
                mTrajectories.Emplace(FString(trajectoryName).ToLower(), trajectory);
            }
        }

        const auto bodyCount = rtPacket->Get6DOFBodyCount();
        for (unsigned int bodyIndex = 0; bodyIndex < bodyCount; bodyIndex++)
        {
            auto bodyName = mRtProtocol->Get6DOFBodyName(bodyIndex);
            if (bodyName == nullptr)
                continue;

            if (rtPacket->Get6DOFBody(bodyIndex, x, y, z, rotationMatrix))
            {
                FQualisysRigidBodyInfo rigidBody;

                // mm to m to world scale and swap x, y positions 
                rigidBody.Position.X = y * positionScalingFactor;
                rigidBody.Position.Y = x * positionScalingFactor;
                rigidBody.Position.Z = z * positionScalingFactor;

                // Handle QTMs standard coordinate setting Z-up
                auto quat = MatrixToQuaternion(rotationMatrix);
                rigidBody.Orientation = FQuat(quat.Y, quat.X, quat.Z, quat.W);
                rigidBody.Index = bodyIndex;

                mRigidBodies.Emplace(FString(bodyName).ToLower(), rigidBody);
            }
        }

        mUpdateLock.Unlock();
    }
}

void AQualisysClient::HandleQtmEvents(CRTPacket * rtPacket)
{
    CRTPacket::EEvent qtmEvent;
    rtPacket->GetEvent(qtmEvent);
    switch (qtmEvent)
    {
        case CRTPacket::EventRTfromFileStarted:
        case CRTPacket::EventConnected:
        case CRTPacket::EventCaptureStarted:
        case CRTPacket::EventCalibrationStarted:
            InitializeQualisysClient();
            if (mUpdateLock.TryLock())
            {
                mTrajectories.Empty();
                mRigidBodies.Empty();
                //mSkeletonPoses.Empty();
            }
            break;
        case CRTPacket::EventRTfromFileStopped:
        case CRTPacket::EventConnectionClosed:
        case CRTPacket::EventCaptureStopped:
        case CRTPacket::EventCalibrationStopped:
            mRtProtocol->StreamFramesStop();
            break;
        case CRTPacket::EventQTMShuttingDown:
            ShutdownQualisysClient();
            break;
    }
}

bool AQualisysClient::GetRigidBody(const FName& rigidBodyName, FQualisysRigidBodyInfo& rigidBody)
{
    CAutoLock lock(&mUpdateLock);
    if (FQualisysRigidBodyInfo* body = mRigidBodies.Find(rigidBodyName.ToString().ToLower()))
    {
        rigidBody = *body;
        return true;
    }
    return false;
}

bool AQualisysClient::GetMarkerPosition(const FName& trajectoryName, FQualisysTrajectoryInfo& trajectoryInfo)
{
    CAutoLock lock(&mUpdateLock);
    if (FQualisysTrajectoryInfo* trajectory = mTrajectories.Find(trajectoryName.ToString().ToLower()))
    {
        trajectoryInfo = *trajectory;
        return true;
    }
    return false;
}

#pragma optimize("", on)

#undef LOCTEXT_NAMESPACE