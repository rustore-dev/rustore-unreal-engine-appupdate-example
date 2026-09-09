using UnrealBuildTool;
using System.IO;

public class RuStoreAppUpdateApp : ModuleRules
{
	public RuStoreAppUpdateApp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RuStoreCore", "RuStoreAppUpdate" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		if (Target.Platform == UnrealTargetPlatform.Android)
        {
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "RuStoreAppUpdateApp_UPL_Android.xml"));
        }
	}
}
