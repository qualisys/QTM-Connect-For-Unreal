// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;

public class QTMConnectLiveLinkEditor : ModuleRules
{
    
    string GetTargetPlatformPathName(ReadOnlyTargetRules Target)
    {
#if UE_5_0_OR_LATER
        return "Win64";
#else
        return Target.Platform == UnrealTargetPlatform.Win32 ? "Win32" : "Win64";
#endif
    }

    bool IsWindowsPlatform(ReadOnlyTargetRules Target)
    {
        bool bWindows =
#if !UE_5_0_OR_LATER
        Target.Platform == UnrealTargetPlatform.Win32 ||
#endif
        Target.Platform == UnrealTargetPlatform.Win64;

        return bWindows;
    }
    
    public QTMConnectLiveLinkEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string rtClientSDKPath = Path.GetFullPath(Path.Combine(PluginDirectory, "Source/ThirdParty/RTClientSDK"));
        string rtClientSDKIncludePath = System.IO.Path.Combine(rtClientSDKPath, "Include");
        string targetPlatformPathName = GetTargetPlatformPathName(Target);
        string rtClientSDKLibPath = Path.Combine(rtClientSDKPath, "Lib", targetPlatformPathName);

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "QTMConnectLiveLinkEditor/Private",
                rtClientSDKIncludePath,
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "UnrealEd",
                "Engine",
                "Projects",
                "DetailCustomizations",
                "QTMConnectLiveLink",
                "LiveLinkInterface",
                "BlueprintGraph"
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "WorkspaceMenuStructure",
                "EditorStyle",
                "SlateCore",
                "Slate",
                "InputCore"
            }
        );

        PublicSystemIncludePaths.Add(rtClientSDKIncludePath);

        if (IsWindowsPlatform(Target))
        {
            PublicAdditionalLibraries.Add(Path.Combine(rtClientSDKLibPath,"RTClientSDK.lib"));
        }
    }
}
