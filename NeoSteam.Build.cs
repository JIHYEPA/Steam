// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NeoSteam : ModuleRules
{
    public NeoSteam(ReadOnlyTargetRules Target) : base(Target)
    {
         PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //bFasterWithoutUnity = true;
        //MinFilesUsingPrecompiledHeader = 1;
        //"HeadMountedDisplay",

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Networking", "UMG", "Slate", "SlateCore", "AIModule" });
    }
}
