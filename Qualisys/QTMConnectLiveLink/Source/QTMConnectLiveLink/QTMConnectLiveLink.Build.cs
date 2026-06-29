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

        // Silence the MSVC C4996 / Clang -Wdeprecated-declarations warnings
        // (strcpy/sprintf/... "unsafe CRT function") emitted by the vendored Qualisys
        // C++ SDK in Private/RTClientSDK. We use UBT's per-module deprecation warning
        // control (UE 5.6+) rather than defining _CRT_SECURE_NO_WARNINGS ourselves: the
        // define collided with the SDK .cpp files' own bare `#define _CRT_SECURE_NO_WARNINGS`
        // (C4005 macro redefinition), and an empty-valued define is dropped by UBT so it
        // suppressed nothing. DeprecationWarningLevel.Off emits /wd4996 for MSVC and
        // -Wno-deprecated-declarations for Clang, so it also covers the Mac/Linux builds.
#if UE_5_6_OR_LATER
        CppCompileWarningSettings.DeprecationWarningLevel = WarningLevel.Off;
#endif

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
