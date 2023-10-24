// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class RuStoreAppUpdate : ModuleRules
{
	public RuStoreAppUpdate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		string publicPath = Path.Combine(ModuleDirectory, "Public");
		string privatePath = Path.Combine(ModuleDirectory, "Private");

		PublicIncludePaths.AddRange(
			new string[]
			{
				publicPath,
				Path.Combine(publicPath, "AsyncNodes"),
			}
		);

		PrivateIncludePaths.AddRange(
			new string[]
			{
				privatePath,
				Path.Combine(privatePath, "AsyncNodes"),
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"RuStoreCore",
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "RuStoreAppUpdate_UPL_Android.xml"));
		}
	}
}
