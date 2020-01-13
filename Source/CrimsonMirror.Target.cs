// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CrimsonMirrorTarget : TargetRules
{
	public CrimsonMirrorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

        /*
         * This is our Steam App ID.
         */
        GlobalDefinitions.Add("UE4_PROJECT_STEAMSHIPPINGID=1220770");

        /*
         * This is used on SetProduct(), and should be the same as your Product Name
         * under Dedicated Game Server Information in Steamworks
         */
        GlobalDefinitions.Add("UE4_PROJECT_STEAMPRODUCTNAME=\"CrimsonMirror\"");

        /*
         * This is used on SetModDir(), and should be the same as your Product Name
         * under Dedicated Game Server Information in Steamworks
         */
        GlobalDefinitions.Add("UE4_PROJECT_STEAMGAMEDIR=\"CrimsonMirror\"");

        /*
         * This is what shows up under the game filter in Steam server browsers.
         */
        GlobalDefinitions.Add("UE4_PROJECT_STEAMGAMEDESC=\"Crimson Mirror\"");

        bUsesSteam = true;
        ExtraModuleNames.AddRange( new string[] { "CrimsonMirror" } );
	}
}
