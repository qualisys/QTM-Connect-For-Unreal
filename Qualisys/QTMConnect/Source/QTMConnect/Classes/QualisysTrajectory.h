// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#pragma once

#include "CoreMinimal.h"
#include "QualisysTrajectory.generated.h"

// Trajectory component
UCLASS(ClassGroup = "Qualisys", meta = (BlueprintSpawnableComponent))
class QTMCONNECT_API UQualisysTrajectory : public UActorComponent
{
    GENERATED_UCLASS_BODY()

    // Name of the rigid body
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Qualisys")
    FName Name;

    // Set to the Qualisys Client actor. If not set it will default to the first found in the World.
    UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Qualisys")
    class AQualisysClient* QualisysClient;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
