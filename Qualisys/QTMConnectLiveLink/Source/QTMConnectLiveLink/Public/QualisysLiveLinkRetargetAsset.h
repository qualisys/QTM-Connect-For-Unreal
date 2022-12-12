// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
#pragma once

#include "BoneIndices.h"
#include "CoreMinimal.h"
#include "LiveLinkRetargetAsset.h"
#include "BonePose.h"
#include "QualisysLiveLinkRetargetAsset.generated.h"

UCLASS(Blueprintable)
class QTMCONNECTLIVELINK_API UQualisysLiveLinkRetargetAsset : public ULiveLinkRetargetAsset
{
    GENERATED_UCLASS_BODY()

    virtual void Initialize() override;
    virtual void BuildPoseFromAnimationData(float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone Mapping")
    TMap<FName, FName> BoneMapping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
    bool DebugTPose;

private:
    TArray<FQuat> TargetLocalPoseCorrections;
    TArray<FCompactPoseBoneIndex> CompactPoseBoneIndices;

    int32 GetSourceBoneIndex(const FCompactPoseBoneIndex& Index);

    FTransform GetWorldPose(const FCompactPose& Pose, const FCompactPoseBoneIndex& Index, bool UsePoseCorrection);
    FTransform GetWorldReferencePose(const FCompactPose& Pose, const FCompactPoseBoneIndex& Index, bool UsePoseCorrection);
};