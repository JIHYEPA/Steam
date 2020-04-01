// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NSPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API UNSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	UNSPlayerAnimInstance();

	// the below functions are the native overrides for each phase
	// Native initialization override point
	//virtual void NativeInitializeAnimation() override;

	// Executed when begin play is called on the owning component
	//virtual void NativeBeginPlay() override;

	//It is usually a good idea to simply gather data in this stepand
	// for the bulk of the work to be done in NativeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayMontage(UAnimMontage* AnimMontage, float PlayRate);

	UFUNCTION()
		void AnimNotify_AttakCombo() {}


	UFUNCTION()
		void AnimNotify_ResetCombo() {}

	bool IsBattleMode;

	bool IsLadder;


};
