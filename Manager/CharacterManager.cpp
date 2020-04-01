// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"
#include "GamePlayFramework/NeoSteamGameInstance.h"
#include "Manager/PuzzleManager.h"
#include "Puzzle/DoorOpen.h"
#include "..//BattleLogic/SpawnActor.h"

UCharacterManager::UCharacterManager()
{
	MonsterArr.Empty();
}

void UCharacterManager::BeginDestroy()
{
	if (MonsterArr.Num() != 0)
	{
		MonsterArr.Empty();
	}

	Super::BeginDestroy();
}

void UCharacterManager::SetGameInstance(UNeoSteamGameInstance* GameInstance)
{
	if (GameInstance != nullptr)
	{
		NSGameInstance = GameInstance;
	}
}

void UCharacterManager::Init(AActor* _SpawnActor)
{
	SpawnActor = Cast<ASpawnActor>(_SpawnActor);

	for (int i = 0; i < SpawnActor->SpawnAmount; ++i)
	{
		SpawnMonster(SpawnActor->SpawnCharacter());
	}
}

void UCharacterManager::SpawnMonster(AActor* _Monster)
{
	if (_Monster == nullptr)
	{
		return;
	}

	if (!MonsterArr.Contains(_Monster))
	{
		MonsterArr.Add(_Monster);
	}
}

void UCharacterManager::DeathMonster(AActor* _Monster)
{
	if (_Monster == nullptr)
	{
		return;
	}

	if (MonsterArr.Contains(_Monster))
	{
		MonsterArr.Remove(_Monster);

		FirstDoorOpen();
	}
}

void UCharacterManager::FirstDoorOpen()
{
	if (NSGameInstance != nullptr)
	{
		if (MonsterArr.Num() <= 0)
		{
			UPuzzleManager* PuzzleMgr = NSGameInstance->GetPuzzleMgr();

			if (PuzzleMgr->GetFirstDoor()->IsAlreadySuccess == false)
			{
				PuzzleMgr->GetFirstDoor()->PuzzleOpen(0);
			}
		}
	}

}	


