// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;

public class QTMConnectLiveLink : ModuleRules
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

    public QTMConnectLiveLink(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        string pluginPublicIncludePath = Path.Combine(ModuleDirectory, "Public");
        string pluginPrivateIncludePath = Path.Combine(ModuleDirectory, "Private");

        string targetPlatformPathName = GetTargetPlatformPathName(Target);

        PublicIncludePaths.AddRange(
            new string[] {
                pluginPublicIncludePath
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                pluginPrivateIncludePath
            }
        );

        bEnableExceptions = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Networking",
                "Sockets",
                "LiveLinkInterface",
                "LiveLink",
#if UE_5_0_OR_LATER
                "LiveLinkAnimationCore",
#endif
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
                "TimeManagement",
#if UE_5_0_OR_LATER
                "LiveLinkAnimationCore",
#endif
            }
        );
    }
}
