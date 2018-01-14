// QTM Connect For Unreal. Copyright 2018 Qualisys
//
#include "CoreMinimal.h"
#include "QualisysRigidBody.h"
#include "QualisysClient.h"

#include "MessageLog.h"
#include "UObjectToken.h"

#define LOCTEXT_NAMESPACE "QTMConnect"

UQualisysRigidBody::UQualisysRigidBody(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
    PrimaryComponentTick.TickGroup = TG_PostPhysics;

    bTickInEditor = false;
    bAutoActivate = true;
}

void UQualisysRigidBody::BeginPlay()
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
            ->AddToken(FTextToken::Create(LOCTEXT("UQualisysRigidBody", "A QualisysRigidBody component should not be a child of a Qualisys Client.")));

        QualisysClient = nullptr;
    }
}

void UQualisysRigidBody::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (QualisysClient == nullptr || GetOwner() == nullptr || GetOwner()->GetRootComponent() == nullptr)
    {
        return;
    }

    FQualisysRigidBodyPose rigidBodyState;
    if (QualisysClient->GetRigidBodyPose(Name, rigidBodyState))
    {
        GetOwner()->GetRootComponent()->SetWorldLocation(rigidBodyState.Position);
        GetOwner()->GetRootComponent()->SetWorldRotation(rigidBodyState.Orientation);
    }
}

#undef LOCTEXT_NAMESPACE
