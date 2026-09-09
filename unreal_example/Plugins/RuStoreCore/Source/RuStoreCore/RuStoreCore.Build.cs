using UnrealBuildTool;
using System.IO;

public class RuStoreCore : ModuleRules
{
	public RuStoreCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Public") });
		PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private") });

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
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

			string[] uplFiles =
			{
				"RuStoreCore_Copies_UPL.xml",
				"RuStoreCore_Gradle_UPL.xml",
			};

			string pluginUplDir = Path.GetFullPath(ModuleDirectory);
			string projectUplDir = GetProjectUplDir(Target);

			foreach (string uplFile in uplFiles)
			{
				string pluginUplPath = Path.GetFullPath(Path.Combine(pluginUplDir, uplFile));
				string projectUplPath = !string.IsNullOrEmpty(projectUplDir) ? Path.GetFullPath(Path.Combine(projectUplDir, uplFile)) : null;
				
				if (!string.IsNullOrEmpty(projectUplPath) && File.Exists(projectUplPath))
				{
					AdditionalPropertiesForReceipt.Add("AndroidPlugin", projectUplPath);
				}
				else
				{
					AdditionalPropertiesForReceipt.Add("AndroidPlugin", pluginUplPath);
				}
			}
		}
	}

	private string GetProjectUplDir(ReadOnlyTargetRules Target)
	{
		// Target.ProjectFile can be null for some build scenarios (e.g. building plugin without a .uproject)
		if (Target.ProjectFile == null)
		{
			return null;
		}

		string projectRoot = Target.ProjectFile.Directory.FullName;
		return Path.Combine(projectRoot, "Source", "RuStoreUPL");
	}
}
