// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleManager.h"
#include "Puzzle/PuzzleBase.h"
#include "Puzzle/DoorOpen.h"

void UPuzzleManager::Init(AActor* _FirstDoor, AActor* _SecondDoor, AActor* _PuzzleBase)
{
	ADoorOpen* Door1 = Cast<ADoorOpen>(_FirstDoor);
	FirstDoor = Door1;

	ADoorOpen* Door2 = Cast<ADoorOpen>(_SecondDoor);
	SecondDoor = Door2;

	APuzzleBase* Puzzle = Cast<APuzzleBase>(_PuzzleBase);
	PuzzleBase = Puzzle;

	DoorIndexSetting();
}

APuzzleBase* UPuzzleManager::GetPuzzleBase()
{
	return PuzzleBase;
}

ADoorOpen* UPuzzleManager::GetFirstDoor()
{
	return FirstDoor;
}

ADoorOpen* UPuzzleManager::GetSecondDoor()
{
	return SecondDoor;
}

int32 UPuzzleManager::GetDoorIndex()
{
	return DoorIndex;
}

void UPuzzleManager::DoorIndexSetting()
{
	if (!FirstDoor->IsAlreadySuccess)
	{
		DoorIndex = 1;
	}
	else if (!SecondDoor->IsAlreadySuccess)
	{
		DoorIndex = 0;
	}
}
