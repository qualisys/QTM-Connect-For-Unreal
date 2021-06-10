// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;

public class QTMConnectLiveLinkEditor : ModuleRules
{
    public QTMConnectLiveLinkEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string rtClientSDKPath = Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty/RTClientSDK"));
        string rtClientSDKIncludePath = System.IO.Path.Combine(rtClientSDKPath, "Include");
        string targetPlatformPathName = "Win64";
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

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicLibraryPaths.Add(rtClientSDKLibPath);
            PublicAdditionalLibraries.Add("RTClientSDK.lib");
        }
    }
}
