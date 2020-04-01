// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API ANSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void ClearPuzzleOpen();

	UFUNCTION(Server, Reliable)
		void ClearPuzzleServer();

	virtual void ClearPuzzleServer_Implementation();

	UFUNCTION(NetMulticast, Reliable)
		void ClearPuzzleMulti();

	virtual void ClearPuzzleMulti_Implementation();
	
	ANSPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UHUD_PlayerLayout> wMainMenu;

	UHUD_PlayerLayout* MyMainMenu;

	//// Override BeginPlay()
	virtual void BeginPlay() override;

public:

	class UNeoSteamGameInstance* NeoSteamGameInstance;


};
