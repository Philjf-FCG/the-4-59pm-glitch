using UnrealBuildTool;
using System.Collections.Generic;

public class The459PMGlitchTarget : TargetRules
{
    public The459PMGlitchTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.Add("Glitch459PM");
    }
}
