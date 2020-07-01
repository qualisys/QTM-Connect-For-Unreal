// QTM Connect For Unreal. Copyright 2018-2020 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;

public class QTMConnectLiveLink : ModuleRules
{
    public QTMConnectLiveLink(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string rtClientSDKPath = Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty/RTClientSDK"));
        string rtClientSDKIncludePath = System.IO.Path.Combine(rtClientSDKPath, "Include");
        string targetPlatformPathName = (Target.Platform == UnrealTargetPlatform.Win32) ? "Win32" : "Win64";
        string rtClientSDKLibPath = Path.Combine(rtClientSDKPath, "Lib", targetPlatformPathName);

        PublicIncludePaths.AddRange(
            new string[] {
                "QTMConnectLiveLink/Public"
            }
        );


        PrivateIncludePaths.AddRange(
            new string[] {
                "QTMConnectLiveLink/Private",
                rtClientSDKIncludePath,
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Networking",
                "Sockets",
                "LiveLinkInterface",
                "LiveLink"
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "LiveLink",
                "LiveLinkInterface",
                "TimeManagement"
            }
        );


        PublicSystemIncludePaths.Add(rtClientSDKIncludePath);

        if (Target.Platform == UnrealTargetPlatform.Win32 ||
        Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicLibraryPaths.Add(rtClientSDKLibPath);
            PublicAdditionalLibraries.Add("RTClientSDK.lib");
        }

    }
}
