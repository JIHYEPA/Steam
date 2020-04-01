// Fill out your copyright notice in the Description page of Project Settings.


#include "NSPlayerAnimInstance.h"


UNSPlayerAnimInstance::UNSPlayerAnimInstance()
{

}

void UNSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

}

void UNSPlayerAnimInstance::PlayMontage(UAnimMontage* AnimMontage, float PlayRate)
{
	if (!Montage_IsPlaying(AnimMontage))
	{
		Montage_Play(AnimMontage, PlayRate);
	}
}
