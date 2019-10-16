// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ZISQLite.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FZISQLiteModule"

void FZISQLiteModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("ZISQLite")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	//FString LibraryPath;
	FString sqlitePath;
#if PLATFORM_WINDOWS
	//LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/ZISQLiteLibrary/Win64/ExampleLibrary.dll"));
	sqlitePath =  FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/ZISQLiteLibrary/Win64/sqlite3.dll"));
#endif
	/*
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/ZISQLiteLibrary/Mac/Release/libExampleLibrary.dylib"));
#endif // PLATFORM_WINDOWS
*/
	//ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	sqliteHandle = !sqlitePath.IsEmpty() ? FPlatformProcess::GetDllHandle(*sqlitePath) : nullptr;

	if (sqliteHandle)
	{
		// Call the test function in the third party library that opens a message box
		//ExampleLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load SQLITE library"));
	}
}

void FZISQLiteModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(sqliteHandle);
	//FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	//ExampleLibraryHandle = nullptr;
	sqliteHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FZISQLiteModule, ZISQLite)
