// Fill out your copyright notice in the Description page of Project Settings.


#include "TriWayPuzzle.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Components/SceneComponent.h"

ATriWayPuzzle::ATriWayPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FuseBoxMesh
	(TEXT("/Game/PostApocalypticCity/StaticMeshes/EnvironmentAssets/Props/FuseBox/SM_FuseBox"));

	if (FuseBoxMesh.Succeeded())
	{
		DefaultMesh->SetStaticMesh(FuseBoxMesh.Object);
	}
}

void ATriWayPuzzle::MiniGameClear()
{
	Super::MiniGameClear();

	//PuzzleBase Delegate(Open) Call
	if (FDele_Open.IsBound() == true)
	{
		FDele_Open.Broadcast();
	}

	IsSuccessed = true;
}
