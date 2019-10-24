// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using UnrealBuildTool;

public class ZLAPI : ModuleRules
{
    
    public ZLAPI(ReadOnlyTargetRules Target) : base(Target)
	{
	    // We're only supporting win64 (x64) for now
	    if (Target.Platform != UnrealTargetPlatform.Win64)
	    {
            throw new Exception("Only Win64 platform is supported");
	    }

	    Type = ModuleType.External;

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bPrecompile = true;
        
        bEnableExceptions = true;

	    // Packaging doesn't support debugging. We don't ship the source files any way so there'd be nothing to be gained from a debug build
	    bool bUseDebugZLAPI = (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.DebugGame);

        string dependenciesDir = ModuleDirectory + "/../../ZLAPI";
	    string binaryDependenciesDir = dependenciesDir + (bUseDebugZLAPI ? "/Debug" : "/Release");
      
        if (bUseDebugZLAPI)
        {
            PublicDefinitions.Add("DEBUG_ZLAPI=1");
        }
        else
        {
            PublicDefinitions.Add("DEBUG_ZLAPI=0");
        }
        
        // Add header paths for Core API and protobuf.
        PublicIncludePaths.Add(Path.Combine(dependenciesDir, "include"));
        PublicIncludePaths.Add(Path.Combine(dependenciesDir, "include/proto"));

        // Static libraries
        PublicLibraryPaths.Add(binaryDependenciesDir);
        PublicAdditionalLibraries.Add("libprotobuf.lib");
	    PublicAdditionalLibraries.Add("ZeroLatencyCppAPI.lib");
        RuntimeDependencies.Add(Path.Combine(binaryDependenciesDir, "ZeroLatencyIPC.dll"));

        // This ensures the build will be run again if any of these dependencies are added/removed/modified.
        // This is important because our build script copies the latest dependencies from another folder
        ExternalDependencies.Add(Path.Combine(binaryDependenciesDir, "ZeroLatencyIPC.dll"));
        ExternalDependencies.Add(Path.Combine(binaryDependenciesDir, "ZeroLatencyCppAPI.lib"));

        // Delay-load the DLL, so we can load it from the right place first
	    PublicDelayLoadDLLs.Add("ZeroLatencyIPC.dll");        
    }
}
