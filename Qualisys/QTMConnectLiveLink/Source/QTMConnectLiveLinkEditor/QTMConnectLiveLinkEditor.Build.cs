// QTM Connect For Unreal. Copyright 2018-2022 Qualisys
//
using Path = System.IO.Path;
using UnrealBuildTool;

public class QTMConnectLiveLinkEditor : ModuleRules
{
    public QTMConnectLiveLinkEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "QTMConnectLiveLinkEditor/Private",
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
                "BlueprintGraph",
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
                "InputCore",
            }
        );
    }
}
