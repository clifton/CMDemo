using UnrealBuildTool;
using System.Collections.Generic;

public class CrimsonMirrorServerTarget : TargetRules
{
    public CrimsonMirrorServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;

        ExtraModuleNames.Add("CrimsonMirror");
    }
}