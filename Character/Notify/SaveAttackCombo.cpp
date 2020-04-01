// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveAttackCombo.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/NeoSteamPlayer.h"

void USaveAttackCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ANeoSteamPlayer* Player = Cast<ANeoSteamPlayer>(MeshComp->GetOwner());

	if (Player != nullptr)
	{
		Player->Execute_Attack(Player);
	}
}
