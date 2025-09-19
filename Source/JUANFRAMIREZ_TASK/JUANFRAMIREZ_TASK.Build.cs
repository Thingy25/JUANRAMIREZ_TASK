// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JUANFRAMIREZ_TASK : ModuleRules
{
	public JUANFRAMIREZ_TASK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
