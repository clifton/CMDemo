// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CrimsonMirror : ModuleRules
{
	public CrimsonMirror(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bFasterWithoutUnity = true;
	
        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "AIModule",
                "NavigationSystem",
                "OnlineSubsystem",
                "OnlineSubsystemUtils",
                "Steamworks",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                // "CustomAnimNode",
                "Slate",
                "SlateCore",
                "OnlineSubsystem",
            }
        );
    }
}
