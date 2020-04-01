// Fill out your copyright notice in the Description page of Project Settings.

#include "InterfaceActor.h"
#include "UObject/CoreNet.h"
#include "UnrealNetwork.h"
#include "Engine.h"

void AInterfaceActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInterfaceActor, IsUsed);
}

// Sets default values
AInterfaceActor::AInterfaceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SceneCompoent = CreateDefaultSubobject<USceneComponent>(FName("SceneCompoent"));
	RootComponent = SceneCompoent;
	DefaultMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	DefaultMesh->SetupAttachment(SceneCompoent);
}


// Called when the game starts or when spawned
void AInterfaceActor::BeginPlay()
{
	Super::BeginPlay();
	IsUsed = false;
}

// Called every frame
//void AInterfaceActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

bool AInterfaceActor::BeginOutlineFocus_Implementation()
{
	if (IsUsed == false)
	{
		DefaultMesh->SetRenderCustomDepth(true);
		return true;
	}

	return false;
}

bool AInterfaceActor::EndOutlineFocus_Implementation()
{
	DefaultMesh->SetRenderCustomDepth(false);
	return false;
}

FString AInterfaceActor::GetInteractionText_Implementation()
{
	if (!IsUsed)
	{
		return InteractionText;
	}

	return FString(TEXT(""));
}

bool AInterfaceActor::Interact_Implementation(APlayerController* playercontroller)
{
	return false;
}

bool AInterfaceActor::BeginShowText_Implementation()
{
	return false;
}

bool AInterfaceActor::EndShowText_Implementation()
{
	return false;
}

bool AInterfaceActor::GetIsUsed_Implementation()
{
	return IsUsed;
}