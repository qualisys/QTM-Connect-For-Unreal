// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#include "QualisysRigidBody.h"

#include "QTMConnect.h"
#include "QualisysClient.h"

#include <Logging/MessageLog.h>
#include <Misc/UObjectToken.h>

#define LOCTEXT_NAMESPACE "QTMConnect"

UQualisysRigidBody::UQualisysRigidBody(const FObjectInitializer& ObjectInitializer) :
    Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bTickEvenWhenPaused = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
    PrimaryComponentTick.TickGroup = TG_PrePhysics;

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

    FQualisysRigidBodyInfo rigidBody;
    if (QualisysClient->GetRigidBody(Name, rigidBody))
    {
        GetOwner()->GetRootComponent()->SetWorldLocationAndRotation(rigidBody.Position, rigidBody.Orientation);
        //GetOwner()->GetRootComponent()->SetWorldRotation();
    }
}

#undef LOCTEXT_NAMESPACE
