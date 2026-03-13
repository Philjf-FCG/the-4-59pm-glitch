using UnrealBuildTool;
using System.Collections.Generic;

public class The459PMGlitchEditorTarget : TargetRules
{
    public The459PMGlitchEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.Add("Glitch459PM");
    }
}
