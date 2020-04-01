// Fill out your copyright notice in the Description page of Project Settings.


#include "NeoSteamGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Puzzle/PuzzleBase.h"
#include "NeoSteam/Character/NSPlayerController.h"
#include "NeoSteam/GamePlayFramework/NeoSteamGameInstance.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

void ANeoSteamGameState::BeginPlay()
{
	Super::BeginPlay();
	NeoSteamGameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());

	//bind function
	if (NeoSteamGameInstance->GetPuzzleMgr()->GetPuzzleBase() != nullptr)
	{
		NeoSteamGameInstance->GetPuzzleMgr()->GetPuzzleBase()->FDele_Open.AddUFunction(this, FName("ClearPuzzle"));
	}
}

void ANeoSteamGameState::ClearPuzzle()
{
	if ((UGameplayStatics::GetPlayerController(this, 0) != nullptr) && (UGameplayStatics::GetPlayerController(this, 1) != nullptr))
	{
		NSPlayerController = Cast<ANSPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		NSPlayerController->ClearPuzzleOpen();

		NSPlayerController_C = Cast<ANSPlayerController>(UGameplayStatics::GetPlayerController(this, 1));
		NSPlayerController_C->ClearPuzzleOpen();
	}
	else
	{
		if (UGameplayStatics::GetPlayerController(this, 0) == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("NULLPTR_0"));
		}
		else if (UGameplayStatics::GetPlayerController(this, 1) == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("NULLPTR_1"));
		}
	}
}
