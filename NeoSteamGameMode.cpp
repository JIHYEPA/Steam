// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "NeoSteamGameMode.h"
#include "HUD/NeoSteamHUD.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "NeoSteamCharacter.h"
#include "DataType/NSEnum.h"
#include "Character/NeoSteamPlayer.h"
#include "Character/NSPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "GamePlayFramework/NeoSteamGameState.h"

ANeoSteamGameMode::ANeoSteamGameMode()
{	
	DefaultPawnClass = ANeoSteamPlayer::StaticClass();
	PlayerControllerClass = ANSPlayerController::StaticClass();
	HUDClass = ANeoSteamHUD::StaticClass();
	GameStateClass = ANeoSteamGameState::StaticClass();
}

void ANeoSteamGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, ErrorMessage);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Options);
	
}
