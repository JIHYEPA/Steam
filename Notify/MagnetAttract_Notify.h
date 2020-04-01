// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BattleLogic/EnumStruct.h"
#include "MagnetAttract_Notify.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API UMagnetAttract_Notify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		FVector StartPosition;
	UPROPERTY(EditAnywhere)
		FVector AttackPosition;
	UPROPERTY(EditAnywhere)
		float AttackRadius;
	UPROPERTY(EditAnywhere)
		ESkillDmg AttackType;

protected:

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};
