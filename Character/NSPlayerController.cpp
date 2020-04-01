// Fill out your copyright notice in the Description page of Project Settings.

#include "NSPlayerController.h"
#include "HUD/HUD_PlayerLayout.h"
#include "UObject/SoftObjectPath.h"
#include "UObject/ConstructorHelpers.h"
#include "Puzzle/PuzzleBase.h"
#include "Puzzle/DoorOpen.h"
#include "NeoSteam/GamePlayFramework/NeoSteamGameInstance.h"

ANSPlayerController::ANSPlayerController()
{

}

void ANSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (wMainMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyMainMenu = CreateWidget<UHUD_PlayerLayout>(GetWorld(), wMainMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyMainMenu)
		{
			//let add it to the view port
			MyMainMenu->AddToViewport();
			MyMainMenu->Init();
		//	MyMainMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ANSPlayerController::ClearPuzzleOpen()
{
	ClearPuzzleServer();
}

void ANSPlayerController::ClearPuzzleServer_Implementation()
{
	ClearPuzzleMulti();
}

void ANSPlayerController::ClearPuzzleMulti_Implementation()
{
	NeoSteamGameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());
	UPuzzleManager* PuzzleMgr = Cast<UPuzzleManager>(NeoSteamGameInstance->GetPuzzleMgr());
	if (!PuzzleMgr->GetPuzzleBase()->IsSuccessed)
	{
		PuzzleMgr->GetSecondDoor()->PuzzleOpen(PuzzleMgr->GetDoorIndex());
	}
}