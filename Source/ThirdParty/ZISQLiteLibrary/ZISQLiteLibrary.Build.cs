// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class ZISQLiteLibrary : ModuleRules
{
	public ZISQLiteLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "x64", "Release"));
			//PublicAdditionalLibraries.Add("ExampleLibrary.lib");
            PublicAdditionalLibraries.Add("sqlite3.lib");

			// Delay-load the DLL, so we can load it from the right place first
			///PublicDelayLoadDLLs.Add("ExampleLibrary.dll");
            PublicDelayLoadDLLs.Add("sqlite3.dll");
		}
        /*
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libExampleLibrary.dylib"));
        }
        */
	}
}
