// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CrimsonMirrorTarget : TargetRules
{
	public CrimsonMirrorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		bUsesSteam = true;
		UEBuildConfiguration.bCompileSteamOSS = true;

		ExtraModuleNames.AddRange( new string[] { "CrimsonMirror" } );
	}
}
