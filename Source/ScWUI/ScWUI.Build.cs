// Scientific Ways

using UnrealBuildTool;

public class ScWUI : ModuleRules
{
	public ScWUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]
		{
			
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"EngineSettings",

			"UMG",
			"CommonUI",
			"SlateCore",

			"InputCore",
			"EnhancedInput",

			"GameplayTags",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Engine",
			"CoreUObject",
		});
	}
}
