using UnrealBuildTool;
using System.Collections.Generic;

public class SpyGameTarget : TargetRules
{
	public SpyGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("SpyGame");
	}
}
