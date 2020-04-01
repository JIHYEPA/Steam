// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleBase.h"
#include "Components/SceneComponent.h"

APuzzleBase::APuzzleBase()
{
	IsSuccessed = false;

	DefaultMesh->SetCollisionProfileName("BlockAll");
}

bool APuzzleBase::Interact_Implementation(APlayerController* playercontroller)
{
	if (IsUsed == false)
	{
		IsUsed = true;
		EndOutlineFocus();
	}
	return false;
}

void APuzzleBase::MiniGameClear()
{

}

void APuzzleBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//Delegate Release
	FDele_Open.Clear();
}