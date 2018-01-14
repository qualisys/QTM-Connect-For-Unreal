// QTM Connect For Unreal. Copyright 2018 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;

public class QTMConnect : ModuleRules
{
    public QTMConnect(ReadOnlyTargetRules Target) : base(Target)
    {
        //Definitions.Add("RTCLIENTSDK_IMPORTS");

        PublicIncludePaths.AddRange(
            new string[] {
                "QTMConnect/Public",
                // ... add public include paths required here ...
            }
        );


        PrivateIncludePaths.AddRange(
            new string[] {
                "QTMConnect/Private",
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

        string rtClientSDKPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty", "RTClientSDK"));
        PublicSystemIncludePaths.Add(System.IO.Path.Combine(rtClientSDKPath, "Include"));

        if (Target.Platform == UnrealTargetPlatform.Win32 ||
            Target.Platform == UnrealTargetPlatform.Win64)
        {
            string targetPlatformPathName = (Target.Platform == UnrealTargetPlatform.Win32) ? "Win32" : "Win64";
            string rtClientSDKBinPath = Path.Combine(rtClientSDKPath, "Lib", targetPlatformPathName);
            PublicLibraryPaths.Add(rtClientSDKBinPath);
            PublicAdditionalLibraries.Add("RTClientSDK.lib");
            PublicDelayLoadDLLs.Add("RTClientSDK.dll");
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(rtClientSDKBinPath, "RTClientSDK.dll")));
        }
    }
}
