// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZLSteamVRController : ModuleRules
{
    public ZLSteamVRController(ReadOnlyTargetRules Target) : base(Target)
    {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bPrecompile = true;
			
        PrivateIncludePathModuleNames.AddRange(new string[]
		{
			"TargetPlatform",
            "ZLSteamVR"
		});

        PrivateDependencyModuleNames.AddRange(new string[]
        {
			"Core",
			"CoreUObject",
			"ApplicationCore",
			"Engine",
			"InputDevice",
            "InputCore",
			"HeadMountedDisplay",
            "ZLSteamVR",
			"OpenVR",
			"OpenGL"
        });

// 		DynamicallyLoadedModuleNames.AddRange(new string[]
// 		{
// 			"SteamVR",
// 		});

		AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenVR");

        if ( Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32 || (Target.Platform == UnrealTargetPlatform.Linux && Target.Architecture.StartsWith("x86_64")) )
        {
            //AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenGL");
            PrivateDependencyModuleNames.Add("OpenGLDrv");
        }
    }
}
