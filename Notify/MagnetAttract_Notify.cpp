// Fill out your copyright notice in the Description page of Project Settings.


#include "MagnetAttract_Notify.h"
#include "Character/NeoSteamPlayer.h"
#include "Components/SkeletalMeshComponent.h"

void UMagnetAttract_Notify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	ANeoSteamPlayer* NeoSteamPlayer = Cast<ANeoSteamPlayer>(MeshComp->GetOwner());
	if (NeoSteamPlayer != nullptr)
	{
		NeoSteamPlayer->NSMagnetAction(StartPosition, AttackPosition, AttackRadius, AttackType);
	}
}