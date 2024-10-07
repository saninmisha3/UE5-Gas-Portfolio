
using UnrealBuildTool;

public class Portfolio : ModuleRules
{
	public Portfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule",
			"GameplayTasks","Niagara","NavigationSystem" });

		
				PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "GameplayAbilities", "GameplayTags", "GameplayTasks", "Niagara", "CableComponent" });
		
				
			}
}
