// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NeoSteamGameState.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API ANeoSteamGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION()
		void ClearPuzzle();

public:

	class UNeoSteamGameInstance* NeoSteamGameInstance;

	class ANSPlayerController* NSPlayerController;
	class ANSPlayerController* NSPlayerController_C;
};
