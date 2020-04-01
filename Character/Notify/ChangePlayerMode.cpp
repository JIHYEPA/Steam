// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangePlayerMode.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/NeoSteamPlayer.h"

void UChangePlayerMode::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ANeoSteamPlayer* Player = Cast<ANeoSteamPlayer>(MeshComp->GetOwner());

	if (Player != nullptr)
	{
		Player->ChangeModeScene();
	}
}