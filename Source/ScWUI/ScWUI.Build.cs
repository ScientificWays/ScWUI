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
			"CoreUObject",

			"EngineSettings",

			"Slate",
			"SlateCore",

			"InputCore",
			"EnhancedInput",

			"GameplayTags",
			"GameFeatures",
			"ModularGameplay",

			"UMG",
			"CommonUI",
			"CommonGame",
			"CommonInput",
			"PropertyPath",
			"PreLoadScreen",

			"UIExtension",
			"ScWGameCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Engine",
			"RenderCore",
			"ApplicationCore",
			"DeveloperSettings",

			//"CommonUser",
			"GameSettings",
		});
	}
}
