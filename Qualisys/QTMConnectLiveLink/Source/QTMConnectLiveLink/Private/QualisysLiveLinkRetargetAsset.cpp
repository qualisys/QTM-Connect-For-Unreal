// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
//
#include "QualisysLiveLinkRetargetAsset.h"

namespace
{
    const TMap<FName, FName> ChildBoneNames =
    {
        {"Hips", "Spine"},
        {"Spine", "Spine1"},
        {"Spine1", "Spine2"},
        {"LeftShoulder", "LeftArm"},
        {"LeftArm", "LeftForeArm"},
        {"LeftForeArm", "LeftHand"},
        {"RightShoulder", "RightArm"},
        {"RightArm", "RightForeArm"},
        {"RightForeArm", "RightHand"},
        {"Spine2", "Neck"},
        {"Neck", "Head"},
        {"LeftUpLeg", "LeftLeg"},
        {"LeftLeg", "LeftFoot"},
        {"RightUpLeg", "RightLeg"},
        {"RightLeg", "RightFoot"}
    };
}

UQualisysLiveLinkRetargetAsset::UQualisysLiveLinkRetargetAsset(const FObjectInitializer& ObjectInitializer):
    Super(ObjectInitializer)
{
    BoneMapping.Add("Hips");
    BoneMapping.Add("Spine");
    BoneMapping.Add("Spine1");
    BoneMapping.Add("Spine2");
    BoneMapping.Add("LeftShoulder");
    BoneMapping.Add("LeftArm");
    BoneMapping.Add("LeftForeArm");
    BoneMapping.Add("LeftHand");
    BoneMapping.Add("RightShoulder");
    BoneMapping.Add("RightArm");
    BoneMapping.Add("RightForeArm");
    BoneMapping.Add("RightHand");
    BoneMapping.Add("Neck");
    BoneMapping.Add("Head");
    BoneMapping.Add("LeftUpLeg");
    BoneMapping.Add("LeftLeg");
    BoneMapping.Add("LeftFoot");
    BoneMapping.Add("LeftToeBase");
    BoneMapping.Add("RightUpLeg");
    BoneMapping.Add("RightLeg");
    BoneMapping.Add("RightFoot");
    BoneMapping.Add("RightToeBase");
}

void UQualisysLiveLinkRetargetAsset::Initialize()
{
}

FMeshPoseBoneIndex GetMeshPoseBoneIndex(const FName& BoneName, const FCompactPose& Pose)
{
    return FMeshPoseBoneIndex(Pose.GetBoneContainer().GetPoseBoneIndexForBoneName(BoneName));
}

FCompactPoseBoneIndex GetCompactPoseBoneIndex(const FName& BoneName, const FCompactPose& Pose)
{
    return Pose.GetBoneContainer().MakeCompactPoseIndex(GetMeshPoseBoneIndex(BoneName, Pose));
}

int32 UQualisysLiveLinkRetargetAsset::GetSourceBoneIndex(const FCompactPoseBoneIndex& Index)
{
    return CompactPoseBoneIndices.Find(Index);
}

FTransform UQualisysLiveLinkRetargetAsset::GetRefPose(const FCompactPose& Pose, const FCompactPoseBoneIndex& Index, bool UsePoseCorrection)
{
    if (Index == INDEX_NONE)
    {
        return FTransform::Identity;
    }

    FTransform PoseCorrection = FTransform::Identity;

    if (UsePoseCorrection)
    {
        const auto SourceBoneIndex = GetSourceBoneIndex(Index);

        if (SourceBoneIndex != INDEX_NONE)
        {
            PoseCorrection = FTransform(LocalPoseCorrections[SourceBoneIndex]);
        }
    }

    return (PoseCorrection * Pose.GetRefPose(Index) * GetRefPose(Pose, Pose.GetParentBoneIndex(Index), UsePoseCorrection));   
}

FVector GetTargetBoneDir(const FName& BoneName)
{
    if ((BoneName == "Hips") ||
        (BoneName == "Spine") ||
        (BoneName == "Spine1") ||
        (BoneName == "Spine2") ||
        (BoneName == "Neck"))
    {
        return FVector(0, 0, 1.0);
    }
    else if ((BoneName == "LeftUpLeg") ||
             (BoneName == "LeftLeg") ||
             (BoneName == "LeftFoot") ||
             (BoneName == "RightUpLeg") ||
             (BoneName == "RightLeg") ||
             (BoneName == "RightFoot"))
    {
        return FVector(0, 0, -1.0);
    }
    else if ((BoneName == "LeftShoulder") ||
             (BoneName == "LeftArm") ||
             (BoneName == "LeftForeArm"))
    {
        return FVector(1.0, 0, 0);
    }
    else if ((BoneName == "RightShoulder") ||
             (BoneName == "RightArm") ||
             (BoneName == "RightForeArm"))
    {
        return FVector(-1.0, 0, 0);
    }

    return FVector(0, 0, 0);
}

void UQualisysLiveLinkRetargetAsset::BuildPoseForSubject(float DeltaTime, const FLiveLinkSubjectFrame& InFrame, FCompactPose& OutPose, FBlendedCurve& OutCurve)
{
    const auto& SourceBoneNames = InFrame.RefSkeleton.GetBoneNames();

    /* Get the target bone names */
    TArray<FName, TMemStackAllocator<>> TargetBoneNames;
    TargetBoneNames.Reserve(SourceBoneNames.Num());

    for (const auto& SourceBoneName : SourceBoneNames)
    {
        auto* TargetBoneName = BoneMapping.Find(SourceBoneName);

        if ((TargetBoneName == nullptr) || ((*TargetBoneName) == "None"))
        {
            TargetBoneNames.Add(SourceBoneName);
        }
        else
        {
            TargetBoneNames.Add(*TargetBoneName);
        }
    }

    const auto SourceLeftLegLength = (
        InFrame.Transforms[SourceBoneNames.Find("LeftUpLeg")].GetTranslation() +
        InFrame.Transforms[SourceBoneNames.Find("LeftLeg")].GetTranslation() +
        InFrame.Transforms[SourceBoneNames.Find("LeftFoot")].GetTranslation() +
        InFrame.Transforms[SourceBoneNames.Find("LeftToeBase")].GetTranslation()).Size();

    const auto SourceRightLegLength = (
        InFrame.Transforms[SourceBoneNames.Find("RightUpLeg")].GetTranslation() +
        InFrame.Transforms[SourceBoneNames.Find("RightLeg")].GetTranslation() +
        InFrame.Transforms[SourceBoneNames.Find("RightFoot")].GetTranslation() +
        InFrame.Transforms[SourceBoneNames.Find("RightToeBase")].GetTranslation()).Size();

    const auto SourceAvgLegLength = ((SourceLeftLegLength + SourceRightLegLength) / 2.0);

    const auto HipsIndex = SourceBoneNames.Find("Hips");
    const auto LeftToeBaseIndex = SourceBoneNames.Find("LeftToeBase");
    const auto RightToeBaseIndex = SourceBoneNames.Find("RightToeBase");

    const auto HipsCompactPoseIndex = GetCompactPoseBoneIndex(TargetBoneNames[HipsIndex], OutPose);
    const auto LeftToeBaseCompactPoseIndex = GetCompactPoseBoneIndex(TargetBoneNames[LeftToeBaseIndex], OutPose);
    const auto RightToeBaseCompactPoseIndex = GetCompactPoseBoneIndex(TargetBoneNames[RightToeBaseIndex], OutPose);

    const auto HipsRefPose = GetRefPose(OutPose, HipsCompactPoseIndex, true);
    const auto LeftToeBaseRefPose = GetRefPose(OutPose, LeftToeBaseCompactPoseIndex, true);
    const auto RightToeBaseRefPose = GetRefPose(OutPose, RightToeBaseCompactPoseIndex, true);

    const auto TargetLeftLegLength = (LeftToeBaseRefPose.GetTranslation() - HipsRefPose.GetTranslation()).Size();
    const auto TargetRightLegLength = (RightToeBaseRefPose.GetTranslation() - HipsRefPose.GetTranslation()).Size();
    const auto TargetAvgLegLength = ((TargetLeftLegLength + TargetRightLegLength) / 2.0);
    const auto TargetLegScale = (TargetAvgLegLength / SourceAvgLegLength);

    CompactPoseBoneIndices.Init(FCompactPoseBoneIndex(INDEX_NONE), SourceBoneNames.Num());
    LocalPoseCorrections.Init(FQuat::Identity, SourceBoneNames.Num());

    for (int32 i = 0; i < TargetBoneNames.Num(); ++i)
    {
        const auto& BoneName = TargetBoneNames[i];
        const auto& BoneTransform = InFrame.Transforms[i];

        const auto BoneIndex = GetCompactPoseBoneIndex(BoneName, OutPose);

        if (BoneIndex == INDEX_NONE)
        {
            continue;
        }

        const auto ParentBoneIndex = OutPose.GetParentBoneIndex(BoneIndex);

        CompactPoseBoneIndices[i] = BoneIndex;

        const auto LocalRefPose = OutPose.GetRefPose(BoneIndex);
        const auto WorldRefPose = GetRefPose(OutPose, BoneIndex, true);
        const auto ParentRefPose = GetRefPose(OutPose, ParentBoneIndex, true);
        const auto WorldToLocal = WorldRefPose.GetRotation().Inverse();

        /* Adjust reference pose into a T-pose */
        const auto* ChildBoneName = ChildBoneNames.Find(SourceBoneNames[i]);

        if (ChildBoneName != nullptr)
        {
            const auto ChildSourceIndex = SourceBoneNames.Find(*ChildBoneName);

            if (ChildSourceIndex != INDEX_NONE)
            {
                /* Find a rotation that takes the reference pose bone direction
                    and transforms it into the desired T-pose direction */
                const auto ChildBoneIndex = GetCompactPoseBoneIndex(TargetBoneNames[ChildSourceIndex], OutPose);

                if (ChildBoneIndex != INDEX_NONE)
                {
                    const auto ChildRefPose = GetRefPose(OutPose, ChildBoneIndex, true);
                    const auto ChildActualDir = (ChildRefPose.GetTranslation() - WorldRefPose.GetTranslation()).GetSafeNormal();
                    const auto ChildTargetDir = GetTargetBoneDir(SourceBoneNames[i]);

                    LocalPoseCorrections[i] = FQuat::FindBetween(WorldToLocal.RotateVector(ChildActualDir), WorldToLocal.RotateVector(ChildTargetDir));
                }
            }
        }
        else if ((SourceBoneNames[i] == "Head") ||
            (SourceBoneNames[i] == "LeftFoot") ||
            (SourceBoneNames[i] == "RightFoot"))
        {
            /* Head/Feet should keep their original world orientation, i.e.
               we want to find a rotation that undoes previous pose corrections */
            const auto OriginalPose = GetRefPose(OutPose, BoneIndex, false);
            const auto CorrectedPose = GetRefPose(OutPose, BoneIndex, true);

            LocalPoseCorrections[i] = (CorrectedPose.GetRotation().Inverse() * OriginalPose.GetRotation());
        }

        auto Pose = FTransform::Identity;

        if ((SourceBoneNames[i] == "Hips") && !DebugTPose)
        {
            Pose.SetTranslation(ParentRefPose.GetRotation().Inverse() * (((TargetLegScale * BoneTransform.GetTranslation()) / ParentRefPose.GetScale3D())));
        }
        else
        {
            Pose.SetTranslation(LocalRefPose.GetTranslation());
        }

        /* Calculate the local bone transform relative to the parent of the
           target bone. Set this to FQuat::Identity to view/debug the T-pose. */
        const auto LocalBoneTransform = (DebugTPose ? FQuat::Identity : (ParentRefPose.GetRotation().Inverse() * BoneTransform.GetRotation() * ParentRefPose.GetRotation()));

        Pose.SetRotation(LocalBoneTransform * LocalRefPose.GetRotation() * LocalPoseCorrections[i]);
        Pose.NormalizeRotation();

        OutPose[BoneIndex] = Pose;
    }
}