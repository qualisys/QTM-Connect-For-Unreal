// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
using System.IO;
using Tools.DotNETCommon;
using UnrealBuildTool;
using System;

public class QTMConnect : ModuleRules
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
    
    
    public QTMConnect(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Public/QTMConnect.h";
        //PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string rtClientSDKPath = Path.Combine(PluginDirectory, "Source/ThirdParty/RTClientSDK");
        string rtClientSDKIncludePath = Path.Combine(rtClientSDKPath, "Include");
        string targetPlatformPathName = GetTargetPlatformPathName(Target);
        string rtClientSDKLibPath = Path.Combine(rtClientSDKPath, "Lib", targetPlatformPathName);
        string pluginPublicIncludePath = Path.Combine(ModuleDirectory, "Public");
        string pluginPrivateIncludePath = Path.Combine(ModuleDirectory, "Private");

        PublicIncludePaths.AddRange(
            new string[] {
                pluginPublicIncludePath
                // ... add public include paths required here ...
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                pluginPrivateIncludePath,
                rtClientSDKIncludePath,
                // ... add other private include paths required here ...
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Projects",
                "CoreUObject",
                "Engine",
                // ... add other public dependencies that you statically link with here ...
            }
        );

        PublicSystemIncludePaths.Add(rtClientSDKIncludePath);

        if (IsWindowsPlatform(Target))
        {
            PublicAdditionalLibraries.Add(Path.Combine(rtClientSDKLibPath, "RTClientSDK.lib"));
        }
    }
}
