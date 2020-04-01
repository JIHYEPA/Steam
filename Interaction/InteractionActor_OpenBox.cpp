// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActor_OpenBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


AInteractionActor_OpenBox::AInteractionActor_OpenBox()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	InteractionText = FString(TEXT("Open"));
	Cover = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cover"));
	Cover->SetupAttachment(DefaultMesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> CreatedParticle(TEXT("/Game/VFX_Toolkit_V1/ParticleSystems/356Days/Par_Carotia.Par_Carotia"));
	Particle = CreatedParticle.Object;
}

bool AInteractionActor_OpenBox::Interact_Implementation(APlayerController* playercontroller)
{
	if (IsUsed == false)
	{
		IsUsed = true;
		EndOutlineFocus();
		OpenBox();
	}
	return false;
}

FString AInteractionActor_OpenBox::GetInteractionText_Implementation()
{
	return InteractionText;
}

bool AInteractionActor_OpenBox::BeginOutlineFocus_Implementation()
{
	if (IsUsed == false)
	{
		DefaultMesh->SetRenderCustomDepth(true);
		Cover->SetRenderCustomDepth(true);
		return true;
	}

	return false;
}

bool AInteractionActor_OpenBox::EndOutlineFocus_Implementation()
{
	DefaultMesh->SetRenderCustomDepth(false);
	Cover->SetRenderCustomDepth(false);
	return false;
}

void AInteractionActor_OpenBox::OpenBox()
{

}
