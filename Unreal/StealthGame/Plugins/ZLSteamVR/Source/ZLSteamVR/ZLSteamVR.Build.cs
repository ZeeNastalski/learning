// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ZLSteamVR : ModuleRules
	{
		public ZLSteamVR(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
            bPrecompile = true;
			
			PrivateIncludePaths.AddRange(
				new string[] {
					"ZLSteamVR/Private",
					EngineDirectory + "/Source/Runtime/Renderer/Private",
					EngineDirectory + "/Source/Runtime/VulkanRHI/Private",
					// ... add other private include paths required here ...
				}
				);

			if(Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
			{
				PrivateIncludePaths.Add(EngineDirectory + "/Source/Runtime/VulkanRHI/Private/Windows");
			}
			else if(Target.Platform != UnrealTargetPlatform.Mac)
			{
				PrivateIncludePaths.Add(EngineDirectory + "/Source/Runtime/VulkanRHI/Private/" + Target.Platform);
			}

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"RHI",
					"RenderCore",
                    "UtilityShaders",
					"Renderer",
					"ShaderCore",
                    "InputCore",
					"HeadMountedDisplay",
					"Slate",
					"SlateCore",
					"ProceduralMeshComponent",
					"ZLCore",
					"OpenVR",
					"OpenGL",
					"Vulkan"
				}
			);
            
            if (Target.bBuildEditor == true)
            {
                PrivateDependencyModuleNames.Add("UnrealEd");
            }

            if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
            {
				//AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenVR");
                PrivateDependencyModuleNames.Add("D3D11RHI");     //@todo steamvr: multiplatform

                //AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenGL");
                PrivateDependencyModuleNames.Add("OpenGLDrv");

                //AddEngineThirdPartyPrivateStaticDependencies(Target, "Vulkan");
                PrivateDependencyModuleNames.Add("VulkanRHI");
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
				PublicFrameworks.Add("IOSurface");
                AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenVR");
                PrivateDependencyModuleNames.AddRange(new string[] { "MetalRHI" });
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux && Target.Architecture.StartsWith("x86_64"))
			{
				AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenVR");
                AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenGL");
				AddEngineThirdPartyPrivateStaticDependencies(Target, "Vulkan");
                PrivateDependencyModuleNames.Add("OpenGLDrv");
                PrivateDependencyModuleNames.Add("VulkanRHI");
            }
		}
	}
}
