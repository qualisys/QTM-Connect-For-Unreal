// QTM Connect For Unreal. Copyright 2018 Qualisys
//
#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Actor.h>

#include "QualisysClient.generated.h"

/*
// Marker
USTRUCT(BlueprintType)
struct FQualisysMarker
{
    GENERATED_USTRUCT_BODY()

    // Position of the marker
    UPROPERTY(BlueprintReadOnly, Category = "Qualisys")
    FVector Position;
};
*/

// RigidBodyPose structure
USTRUCT(BlueprintType)
struct FQualisysRigidBodyPose
{
    GENERATED_USTRUCT_BODY()

    // Position of the rigid body
    UPROPERTY(BlueprintReadOnly, Category = "Qualisys")
    FVector Position;

    // Orientation of the rigid body
    UPROPERTY(BlueprintReadOnly, Category = "Qualisys")
    FQuat Orientation;
};

// Qualisys streaming client actor
UCLASS()
class QTMCONNECT_API AQualisysClient : public AActor
{
    GENERATED_UCLASS_BODY()

public:
    // IP address to the machine running Qualisys Track Manager
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    FString IPAddressToQTMServer;

    // UDP port for streaming (0 = uses TCP for streaming instead of UDP)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    int UdpPort;

    // Streaming rate (0 = As fast as possible)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    int StreamRate;

    /*
    * Retrieves available FQualisysRigidBodyPose for the rigid body.
    * The translation of the Qualisys Client actor is applied to the pose.
    *
    * @param RigidBody Name of the rigid body
    * @param RigidBodyPose Receives latest available rigid body state (if any).
    * @return True if any rigid body state was available for the specified name.
    */
    UFUNCTION(BlueprintCallable, Category = "Qualisys")
    bool GetRigidBodyPose(FString RigidBody, FQualisysRigidBodyPose& RigidBodyPose);

    /*
    * Convenience function for finding a Qualisys Client actor streaming object.
    * @return The first AQualisysClient actor found in @World.
    */
    UFUNCTION(BlueprintCallable, Category = "Qualisys")
    static AQualisysClient* FindQualisysClient(UWorld* World);

protected:
    virtual void PreInitializeComponents() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

private:
    bool GetRigidBodyPoseUntransformedByClient(FString rigidBody, FQualisysRigidBodyPose& rigidBodyPose);

    void InitializeQualisysClient();
    void ShutdownQualisysClient();

    class CRTProtocol* mRTProtocol;
    int mLastFrameNumber;

    FCriticalSection mUpdateLock;
    //TMap<FString, FQualisysMarker> mMarkerPositions;
    TMap<FString, FQualisysRigidBodyPose> mRigidBodyPoses;
};