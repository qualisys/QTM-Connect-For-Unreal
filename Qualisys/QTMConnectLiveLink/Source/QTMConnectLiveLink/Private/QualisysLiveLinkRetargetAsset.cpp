// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
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
        {"LeftHandThumb1", "LeftHandThumb2"},
        {"LeftHandThumb2", "LeftHandThumb3"},
        {"LeftHandIndex1", "LeftHandIndex2"},
        {"LeftHandIndex2", "LeftHandIndex3"},
        {"LeftHandMiddle1", "LeftHandMiddle2"},
        {"LeftHandMiddle2", "LeftHandMiddle3"},
        {"LeftHandRing1", "LeftHandRing2"},
        {"LeftHandRing2", "LeftHandRing3"},
        {"LeftHandPinky1", "LeftHandPinky2"},
        {"LeftHandPinky2", "LeftHandPinky3"},
        {"RightShoulder", "RightArm"},
        {"RightArm", "RightForeArm"},
        {"RightForeArm", "RightHand"},
        {"RightHandThumb1", "RightHandThumb2"},
        {"RightHandThumb2", "RightHandThumb3"},
        {"RightHandIndex1", "RightHandIndex2"},
        {"RightHandIndex2", "RightHandIndex3"},
        {"RightHandMiddle1", "RightHandMiddle2"},
        {"RightHandMiddle2", "RightHandMiddle3"},
        {"RightHandRing1", "RightHandRing2"},
        {"RightHandRing2", "RightHandRing3"},
        {"RightHandPinky1", "RightHandPinky2"},
        {"RightHandPinky2", "RightHandPinky3"},
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
    BoneMapping.Add("LeftInHandThumb");
    BoneMapping.Add("LeftHandThumb1");
    BoneMapping.Add("LeftHandThumb2");
    BoneMapping.Add("LeftHandThumb3");
    BoneMapping.Add("LeftInHandIndex");
    BoneMapping.Add("LeftHandIndex1");
    BoneMapping.Add("LeftHandIndex2");
    BoneMapping.Add("LeftHandIndex3");
    BoneMapping.Add("LeftInHandMiddle");
    BoneMapping.Add("LeftHandMiddle1");
    BoneMapping.Add("LeftHandMiddle2");
    BoneMapping.Add("LeftHandMiddle3");
    BoneMapping.Add("LeftInHandRing");
    BoneMapping.Add("LeftHandRing1");
    BoneMapping.Add("LeftHandRing2");
    BoneMapping.Add("LeftHandRing3");
    BoneMapping.Add("LeftInHandPinky");
    BoneMapping.Add("LeftHandPinky1");
    BoneMapping.Add("LeftHandPinky2");
    BoneMapping.Add("LeftHandPinky3");
    BoneMapping.Add("RightShoulder");
    BoneMapping.Add("RightArm");
    BoneMapping.Add("RightForeArm");
    BoneMapping.Add("RightHand");
    BoneMapping.Add("RightInHandThumb");
    BoneMapping.Add("RightHandThumb1");
    BoneMapping.Add("RightHandThumb2");
    BoneMapping.Add("RightHandThumb3");
    BoneMapping.Add("RightInHandIndex");
    BoneMapping.Add("RightHandIndex1");
    BoneMapping.Add("RightHandIndex2");
    BoneMapping.Add("RightHandIndex3");
    BoneMapping.Add("RightInHandMiddle");
    BoneMapping.Add("RightHandMiddle1");
    BoneMapping.Add("RightHandMiddle2");
    BoneMapping.Add("RightHandMiddle3");
    BoneMapping.Add("RightInHandRing");
    BoneMapping.Add("RightHandRing1");
    BoneMapping.Add("RightHandRing2");
    BoneMapping.Add("RightHandRing3");
    BoneMapping.Add("RightInHandPinky");
    BoneMapping.Add("RightHandPinky1");
    BoneMapping.Add("RightHandPinky2");
    BoneMapping.Add("RightHandPinky3");
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

FTransform UQualisysLiveLinkRetargetAsset::GetWorldPose(const FCompactPose& Pose, const FCompactPoseBoneIndex& Index, bool UsePoseCorrection)
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
            PoseCorrection = FTransform(TargetLocalPoseCorrections[SourceBoneIndex]);
        }
    }

    return (PoseCorrection * Pose[Index] * GetWorldPose(Pose, Pose.GetParentBoneIndex(Index), UsePoseCorrection));
}

FTransform UQualisysLiveLinkRetargetAsset::GetWorldReferencePose(const FCompactPose& Pose, const FCompactPoseBoneIndex& Index, bool UsePoseCorrection)
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
            PoseCorrection = FTransform(TargetLocalPoseCorrections[SourceBoneIndex]);
        }
    }

    return (PoseCorrection * Pose.GetRefPose(Index) * GetWorldReferencePose(Pose, Pose.GetParentBoneIndex(Index), UsePoseCorrection));
}

FVector GetTargetBoneDirection(const FName& BoneName)
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
             (BoneName == "LeftForeArm") ||
             (BoneName == "LeftHandIndex1") ||
             (BoneName == "LeftHandIndex2") ||
             (BoneName == "LeftHandMiddle1") ||
             (BoneName == "LeftHandMiddle2") ||
             (BoneName == "LeftHandRing1") ||
             (BoneName == "LeftHandRing2") ||
             (BoneName == "LeftHandPinky1") ||
             (BoneName == "LeftHandPinky2"))
    {
        return FVector(1.0, 0, 0);
    }
    else if ((BoneName == "LeftHandThumb1") ||
             (BoneName == "LeftHandThumb2"))
    {
        return FVector(0.70710676908493042, 0.66446298360824585, -0.24184474349021912); // Euler(-20.0, 0.0, 45.0) * Vector(1.0, 0.0, 0.0)
    }
    else if ((BoneName == "RightShoulder") ||
             (BoneName == "RightArm") ||
             (BoneName == "RightForeArm") ||
             (BoneName == "RightHandIndex1") ||
             (BoneName == "RightHandIndex2") ||
             (BoneName == "RightHandMiddle1") ||
             (BoneName == "RightHandMiddle2") ||
             (BoneName == "RightHandRing1") ||
             (BoneName == "RightHandRing2") ||
             (BoneName == "RightHandPinky1") ||
             (BoneName == "RightHandPinky2"))
    {
        return FVector(-1.0, 0, 0);
    }
    else if ((BoneName == "RightHandThumb1") ||
             (BoneName == "RightHandThumb2"))
    {
        return FVector(-0.70710676908493042, 0.66446298360824585, -0.24184474349021912); // Euler(-20.0, 0.0, -45.0) * Vector(-1.0, 0.0, 0.0)
    }

    return FVector(0, 0, 0);
}

/* Rotate 180 degrees around Z-axis */
FTransform Rotate180(const FTransform& Transform)
{
    const auto Rotation = Transform.GetRotation();
    const auto Location = Transform.GetLocation();

    return FTransform(FQuat(-Rotation.X, -Rotation.Y, Rotation.Z, Rotation.W), FVector(-Location.X, -Location.Y, Location.Z));
}

void UQualisysLiveLinkRetargetAsset::BuildPoseFromAnimationData(float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose)
{
    const auto& SourceBoneNames = InSkeletonData->GetBoneNames();

    /* Make sure this is a QTM skeleton */
    if (SourceBoneNames.Find("Hips") == INDEX_NONE)
    {
        return;
    }

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
        InFrameData->Transforms[SourceBoneNames.Find("LeftUpLeg")].GetTranslation() +
        InFrameData->Transforms[SourceBoneNames.Find("LeftLeg")].GetTranslation() +
        InFrameData->Transforms[SourceBoneNames.Find("LeftFoot")].GetTranslation() +
        InFrameData->Transforms[SourceBoneNames.Find("LeftToeBase")].GetTranslation()).Size();

    const auto SourceRightLegLength = (
        InFrameData->Transforms[SourceBoneNames.Find("RightUpLeg")].GetTranslation() +
        InFrameData->Transforms[SourceBoneNames.Find("RightLeg")].GetTranslation() +
        InFrameData->Transforms[SourceBoneNames.Find("RightFoot")].GetTranslation() +
        InFrameData->Transforms[SourceBoneNames.Find("RightToeBase")].GetTranslation()).Size();

    const auto SourceAvgLegLength = ((SourceLeftLegLength + SourceRightLegLength) / 2.0);

    const auto SourceHipsIndex = SourceBoneNames.Find("Hips");
    const auto SourceLeftToeBaseIndex = SourceBoneNames.Find("LeftToeBase");
    const auto SourceRightToeBaseIndex = SourceBoneNames.Find("RightToeBase");

    const auto TargetHipsIndex = GetCompactPoseBoneIndex(TargetBoneNames[SourceHipsIndex], OutPose);
    const auto TargetLeftToeBaseIndex = GetCompactPoseBoneIndex(TargetBoneNames[SourceLeftToeBaseIndex], OutPose);
    const auto TargetRightToeBaseIndex = GetCompactPoseBoneIndex(TargetBoneNames[SourceRightToeBaseIndex], OutPose);

    const auto TargetHipsReferencePose = GetWorldReferencePose(OutPose, TargetHipsIndex, true);
    const auto TargetLeftToeBaseReferencePose = GetWorldReferencePose(OutPose, TargetLeftToeBaseIndex, true);
    const auto TargetRightToeBaseReferencePose = GetWorldReferencePose(OutPose, TargetRightToeBaseIndex, true);

    const auto TargetLeftLegLength = (TargetLeftToeBaseReferencePose.GetTranslation() - TargetHipsReferencePose.GetTranslation()).Size();
    const auto TargetRightLegLength = (TargetRightToeBaseReferencePose.GetTranslation() - TargetHipsReferencePose.GetTranslation()).Size();
    const auto TargetAvgLegLength = ((TargetLeftLegLength + TargetRightLegLength) / 2.0);
    const auto TargetLegScale = (TargetAvgLegLength / SourceAvgLegLength);

    CompactPoseBoneIndices.Init(FCompactPoseBoneIndex(INDEX_NONE), SourceBoneNames.Num());
    TargetLocalPoseCorrections.Init(FQuat::Identity, SourceBoneNames.Num());

    for (int32 i = 0; i < TargetBoneNames.Num(); ++i)
    {
        const auto BoneName = TargetBoneNames[i];
        const auto BoneIndex = GetCompactPoseBoneIndex(BoneName, OutPose);

        if (BoneIndex == INDEX_NONE)
        {
            continue;
        }

        FTransform SourceWorldPose;

        if (!DebugTPose)
        {
            for (auto j = i; (j != INDEX_NONE); j = InSkeletonData->BoneParents[j])
            {
                SourceWorldPose *= Rotate180(InFrameData->Transforms[j]);
            }
        }

        const auto ParentBoneIndex = OutPose.GetParentBoneIndex(BoneIndex);

        CompactPoseBoneIndices[i] = BoneIndex;

        const auto TargetLocalReferencePose = OutPose.GetRefPose(BoneIndex);
        const auto TargetWorldReferencePose = GetWorldReferencePose(OutPose, BoneIndex, true);
        const auto TargetParentWorldReferencePose = GetWorldReferencePose(OutPose, ParentBoneIndex, true);
        const auto TargetWorldToLocal = TargetWorldReferencePose.GetRotation().Inverse();

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
                    const auto ChildReferencePose = GetWorldReferencePose(OutPose, ChildBoneIndex, true);
                    const auto ChildActualDirection = (ChildReferencePose.GetTranslation() - TargetWorldReferencePose.GetTranslation()).GetSafeNormal();
                    const auto ChildTargetDirection = GetTargetBoneDirection(SourceBoneNames[i]);

                    TargetLocalPoseCorrections[i] = FQuat::FindBetween(TargetWorldToLocal.RotateVector(ChildActualDirection), TargetWorldToLocal.RotateVector(ChildTargetDirection));
                }
            }
        }
        else if ((SourceBoneNames[i] == "Head") ||
                 (SourceBoneNames[i] == "LeftFoot") ||
                 (SourceBoneNames[i] == "RightFoot"))
        {
            /* Head/Feet should keep their original world orientation, i.e.
               we want to find a rotation that undoes previous pose corrections */
            const auto OriginalPose = GetWorldReferencePose(OutPose, BoneIndex, false);
            const auto CorrectedPose = GetWorldReferencePose(OutPose, BoneIndex, true);

            TargetLocalPoseCorrections[i] = (CorrectedPose.GetRotation().Inverse() * OriginalPose.GetRotation());
        }

        auto Pose = FTransform::Identity;

        if ((SourceBoneNames[i] == "Hips") && !DebugTPose)
        {
            Pose.SetTranslation(TargetParentWorldReferencePose.GetRotation().Inverse() * (((TargetLegScale * SourceWorldPose.GetTranslation()) / TargetParentWorldReferencePose.GetScale3D())));
        }
        else
        {
            Pose.SetTranslation(TargetLocalReferencePose.GetTranslation());
        }

        /* We want to find an offset such that Target_World = Offset_World * Source_World. We do this by using the reference poses, i.e.
           Offset_World = TargetReferencePose_World * SourceRefPose_World.Inverse(). However, SourceRefPose_World is identity, so we end up with
           Offset_World = TargetReferencePose_World * Identity.Inverse() <=> OffsetWorld = TargetReferencePose_World. To get the local target rotation, we
           can then use Target_Local = Offset_World * Source_World * TargetParent_World.Inverse() */
        const auto TargetLocalPose = (GetWorldReferencePose(OutPose, BoneIndex, true) * SourceWorldPose * GetWorldPose(OutPose, ParentBoneIndex, false).Inverse());

        Pose.SetRotation(TargetLocalPose.GetRotation());
        Pose.NormalizeRotation();

        OutPose[BoneIndex] = Pose;
    }
}