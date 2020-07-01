// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Actor.h>

#include "QualisysClient.generated.h"

class CRTPacket;

// Trajectory
USTRUCT(BlueprintType)
struct FQualisysTrajectoryInfo
{
    GENERATED_USTRUCT_BODY()

    // Position of the trajectory
    UPROPERTY(BlueprintReadOnly, Category = "Qualisys")
    FVector Position;

    unsigned int Index;
};

// RigidBody structure
USTRUCT(BlueprintType)
struct FQualisysRigidBodyInfo
{
    GENERATED_USTRUCT_BODY()

    // Position of the rigid body
    UPROPERTY(BlueprintReadOnly, Category = "Qualisys")
    FVector Position;

    // Orientation of the rigid body
    UPROPERTY(BlueprintReadOnly, Category = "Qualisys")
    FQuat Orientation;

    unsigned int Index;
};

class CAutoLock
{
public:
    CAutoLock(FCriticalSection* lock) : mLock(lock)
    {
        mLock->Lock();
    }
    ~CAutoLock()
    {
        mLock->Unlock();
    }
private:
    FCriticalSection* mLock;
};

// Qualisys streaming client actor
UCLASS()
class QTMCONNECT_API AQualisysClient : public AActor
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    bool AutoDiscoverQTMServer;

    // IP address to the machine running Qualisys Track Manager
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    FString IPAddressToQTMServer;

    // Streaming rate (0 = As fast as possible)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    int StreamRate;

    // Debug flag for viewing all streamed rigid bodies and their coordinate systems
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    bool DebugDrawingRigidBodies;

    // Debug flag for viewing all streamed labeled trajectories
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    bool DebugDrawingTrajectories;

    // Retrieves available FQualisysRigidBody for the given rigid body name.
    // @param Name of the rigid body
    // @param RigidBody Receives latest available rigid body transform (if any).
    // @return True if any rigid body transform was available for the specified name.
    UFUNCTION(BlueprintCallable, Category = "Qualisys")
    bool GetRigidBody(const FName &rigidBodyName, FQualisysRigidBodyInfo& rigidBody);

    // Retrieves available FQualisysTrajectory for the given trajectory name.
    // @param Name of the Trajectory
    // @param Trajectory Receives latest available trajectory position (if any).
    // @return True if any trajectory information was available for the specified name.
    UFUNCTION(BlueprintCallable, Category = "Qualisys")
    bool GetMarkerPosition(const FName &trajectoryName, FQualisysTrajectoryInfo& trajectory);

    // Finding a Qualisys Client actor streaming object in the world.
    // @return The first AQualisysClient actor found in @World.
    UFUNCTION(BlueprintCallable, Category = "Qualisys")
    static AQualisysClient* FindQualisysClient(UWorld* World);

protected:
    virtual void PreInitializeComponents() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

    static void ConvertQtmColorToUE(unsigned int qtmColor, FColor &color);

    void HandleQtmData(CRTPacket * rtPacket);
    void HandleQtmEvents(CRTPacket * rtPacket);

private:
    void InitializeQualisysClient();
    void ShutdownQualisysClient();

    class CRTProtocol* mRtProtocol;

    FCriticalSection mUpdateLock;
    TMap<FString, FQualisysTrajectoryInfo> mTrajectories;
    TMap<FString, FQualisysRigidBodyInfo> mRigidBodies;
};