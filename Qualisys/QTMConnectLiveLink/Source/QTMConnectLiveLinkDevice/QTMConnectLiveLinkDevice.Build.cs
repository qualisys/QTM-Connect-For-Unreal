// QTM Connect For Unreal. Copyright 2018-2026 Qualisys
//
// Editor-only module that exposes a Live Link Hub "device" for QTM, implementing
// the connection and recording capabilities introduced in Unreal Engine 5.8.
//
// NOTE: This module is hard-gated to UE 5.8+. Older engine versions don't ship
// the LiveLinkDevice plugin so the module won't compile against them. If you
// need to keep building the rest of QTMConnectLiveLink on UE <= 5.7, omit this
// module from the .uplugin in your branch.
using UnrealBuildTool;

public class QTMConnectLiveLinkDevice : ModuleRules
{
    public QTMConnectLiveLinkDevice(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "Projects",
                // The runtime module owns FQTMRecordingController (which wraps the
                // vendored RT SDK) and exports it via QTMCONNECTLIVELINK_API.
                "QTMConnectLiveLink",
                "LiveLinkDevice",
                "LiveLinkHub",
                "LiveLinkInterface", // ILiveLinkRecordingSession (UE 5.8+)
            }
        );
    }
}
