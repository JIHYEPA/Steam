// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionActor_NPC_Sparrow.h"

#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"


AInteractionActor_NPC_Sparrow::AInteractionActor_NPC_Sparrow()
{
	InteractionText = FString(TEXT("Speak"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	InteractionCam = CreateDefaultSubobject<UCameraComponent>(TEXT("IneteractionCam"));
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));

	SkeletalMesh->SetupAttachment(RootComponent);
	InteractionCam->SetupAttachment(RootComponent);
	Billboard->SetupAttachment(RootComponent);
	TextRender->SetupAttachment(RootComponent);
}

bool AInteractionActor_NPC_Sparrow::BeginOutlineFocus_Implementation()
{
	SkeletalMesh->SetRenderCustomDepth(true);
	Billboard->SetVisibility(true);
	FRotator Rotator = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraRotation();
	Rotator = Rotator * (-1.0f);
	TextRender->SetWorldRotation(Rotator);
	TextRender->SetVisibility(true);
	return false;
}

bool AInteractionActor_NPC_Sparrow::EndOutlineFocus_Implementation()
{
	SkeletalMesh->SetRenderCustomDepth(false);
	Billboard->SetVisibility(false);
	TextRender->SetVisibility(false);
	return false;
}

bool AInteractionActor_NPC_Sparrow::Interact_Implementation(APlayerController* playercontroller)
{
	EndOutlineFocus();
	if (IsValid(playercontroller))
	{
		OpenUI(playercontroller);
	}

	return false;
}
