// QTM Connect For Unreal. Copyright 2018-2019 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;
using System;

public class QTMConnect : ModuleRules
{
    public QTMConnect(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Public/QTMConnect.h";
        //PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        string rtClientSDKPath = Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty/RTClientSDK"));
        string rtClientSDKIncludePath = System.IO.Path.Combine(rtClientSDKPath, "Include");
        string targetPlatformPathName = (Target.Platform == UnrealTargetPlatform.Win32) ? "Win32" : "Win64";
        string rtClientSDKLibPath = Path.Combine(rtClientSDKPath, "Lib", targetPlatformPathName);

        PublicIncludePaths.AddRange(
            new string[] {
                "QTMConnect/Public",
                // ... add public include paths required here ...
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
                "QTMConnect/Private",
                rtClientSDKIncludePath,
                // ... add other private include paths required here ...
            }
        );

        // Adding your definition here, will add a global Preprocessor value for cpp
        //Definitions.Add("QTM_RTCLIENTSDK_LIB_DIR=" + targetPlatformPathName/RTClientSDK + "");

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


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                // ... add private dependencies that you statically link with here ...
            }
        );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
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
