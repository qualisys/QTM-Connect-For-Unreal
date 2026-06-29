// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;

public class QTMConnectLiveLink : ModuleRules
{
    public QTMConnectLiveLink(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bWarningsAsErrors = false;

        bEnableExceptions = true;

        ShadowVariableWarningLevel = WarningLevel.Off;

        // Silence MSVC C4996 "unsafe CRT function" warnings (strcpy/sprintf/...) coming
        // from the vendored Qualisys C++ SDK (Private/RTClientSDK). The SDK is shared
        // cross-platform code; we suppress here rather than editing the vendored source.
        PrivateDefinitions.Add("_CRT_SECURE_NO_WARNINGS");

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Public")
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private"),
                Path.Combine(ModuleDirectory, "Private/RtClientSDK/External/tinyxml2")
            }
        );

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
