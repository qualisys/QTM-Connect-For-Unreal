// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#include "QualisysTrajectory.h"

#include "QTMConnect.h"
#include "QualisysClient.h"

#include <Logging/MessageLog.h>
#include <Misc/UObjectToken.h>

#define LOCTEXT_NAMESPACE "QTMConnect"

UQualisysTrajectory::UQualisysTrajectory(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bTickEvenWhenPaused = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
    PrimaryComponentTick.TickGroup = TG_PrePhysics;

    bTickInEditor = false;
    bAutoActivate = true;
}

void UQualisysTrajectory::BeginPlay()
{
    Super::BeginPlay();

    if (QualisysClient == nullptr)
    {
        QualisysClient = AQualisysClient::FindQualisysClient(GetWorld());
    }

    if (Cast<AQualisysClient>(GetOwner()))
    {
        FMessageLog("PIE").Error()
            ->AddToken(FUObjectToken::Create(GetOwner()))
            ->AddToken(FTextToken::Create(LOCTEXT("UQualisysTrajectory", "A QualisysTrajectory component should not be a child of a Qualisys Client.")));

        QualisysClient = nullptr;
    }
}

void UQualisysTrajectory::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (QualisysClient == nullptr || GetOwner() == nullptr || GetOwner()->GetRootComponent() == nullptr)
    {
        return;
    }

    FQualisysTrajectoryInfo trajectory;
    if (QualisysClient->GetMarkerPosition(Name, trajectory))
    {
        GetOwner()->GetRootComponent()->SetWorldLocation(trajectory.Position);
    }
}

#undef LOCTEXT_NAMESPACE
