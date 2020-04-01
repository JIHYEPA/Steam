// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeAttack_Notify.h"
#include "NeoSteamCharacter.h"
#include "Components/SkeletalMeshComponent.h"

void URangeAttack_Notify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ANeoSteamCharacter* NeoSteamCharacter = Cast<ANeoSteamCharacter>(MeshComp->GetOwner());
	if (NeoSteamCharacter != nullptr)
	{
		NeoSteamCharacter->NSCreateAttackCollision(StartPosition, AttackPosition, AttackRadius, AttackType);
	}
}
