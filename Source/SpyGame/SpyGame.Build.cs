using UnrealBuildTool;

public class SpyGame : ModuleRules
{
	public SpyGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore", "UMG"
		});
	}
}
