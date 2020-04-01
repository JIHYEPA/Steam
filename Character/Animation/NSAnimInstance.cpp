// Fill out your copyright notice in the Description page of Project Settings.


#include "NSAnimInstance.h"
#include "NeoSteam/NeoSteamCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UNSAnimInstance::UNSAnimInstance()
{

}

void UNSAnimInstance::NativeInitializeAnimation()
{

}

void UNSAnimInstance::NativeBeginPlay()
{
	//Appear Montage
}

void UNSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	ANeoSteamCharacter* Character = Cast<ANeoSteamCharacter>(TryGetPawnOwner());

	if (Character != nullptr)
	{
		IsAir = Character->GetMovementComponent()->IsFalling();

		bPushTarget = Character->bPushTarget;

		bPushEnd = Character->bPushEnd;

		MoveSpeed = Character->GetVelocity().Size();

		IsAccelerating = (Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false);
	}
}
