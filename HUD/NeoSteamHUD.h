// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HUD_PlayerLayout.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NeoSteamHUD.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API ANeoSteamHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ANeoSteamHUD();


	UFUNCTION()
		void EndInterfaceText();

	virtual void BeginPlay() override;
};
