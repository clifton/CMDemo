using UnrealBuildTool;
using System.Collections.Generic;

public class CrimsonMirrorServerTarget : TargetRules
{
    public CrimsonMirrorServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        
        bUsesSteam = true;

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

        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.Add("CrimsonMirror");
    }
}