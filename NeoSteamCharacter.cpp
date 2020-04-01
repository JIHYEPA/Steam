// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NeoSteamCharacter.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimBlueprint.h"
#include "DrawDebugHelpers.h"
#include "Character/NeoSteamPlayer.h"
#include "Character/NeoSteamMonster.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/LevelMontage.h"
#include "Components/MeshComponent.h"

#include "GameFramework/Controller.h"
#include "GamePlayFramework/NeoSteamGameInstance.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "BattleLogic/BattleLogic.h"



//////////////////////////////////////////////////////////////////////////
// ANeoSteamCharacter

ANeoSteamCharacter::ANeoSteamCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LevelMontage = ObjectInitializer.CreateDefaultSubobject<ULevelMontage>(this, TEXT("MontageComponent"));
	AddOwnedComponent(LevelMontage);

	//PrimaryComponentTick.bCanEverTick = true;

	//// set our turn rates for input
	//BaseTurnRate = 45.f;
	//BaseLookUpRate = 45.f;

	//// Don't rotate when the controller rotates. Let that just affect the camera.
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	//// Configure character movement
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	//GetCharacterMovement()->JumpZVelocity = 600.f;
	//GetCharacterMovement()->AirControl = 0.2f;
}

void ANeoSteamCharacter::Init(ENSCharacterID CharacterID)
{	
	ID = CharacterID;

	UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());
	const FNSCharacterInfo& InfoTable = GameInstance->GetCharacterInfo(ID);

	//Load
	Status = GameInstance->GetCharacterStatusTable(ID);

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	//Asset Load
	GetCapsuleComponent()->SetCapsuleHalfHeight(InfoTable.CapsuleHalfHeight);
	GetCapsuleComponent()->SetCapsuleRadius(InfoTable.CapsuleRadius);
	GetCapsuleComponent()->SetCollisionProfileName(InfoTable.CollisionPreset);

	GetMesh()->SetSkeletalMesh(Cast<USkeletalMesh>(InfoTable.Mesh_Skin0.TryLoad()));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -InfoTable.CapsuleHalfHeight), FQuat(FRotator(0.f, -90.f, 0.f)));

	UAnimBlueprint* AnimBP = Cast<UAnimBlueprint>(InfoTable.AnimBlueprint.TryLoad());

	if (AnimBP != nullptr)
	{
		GetMesh()->SetAnimInstanceClass(AnimBP->GetAnimBlueprintGeneratedClass());

		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ANeoSteamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ANeoSteamCharacter::AddHealthPoint(float Hp)
{	
	Status.Hp += Hp;

	if (Status.Hp <= 0)
	{
		Status.Hp = 0.f;
			
		//Death_Implementation();

		return false;
	}
	
	return true;
}

//void ANeoSteamCharacter::MoveForward(float Value)
//{
//	if ((Controller != NULL) && (Value != 0.0f))
//	{
//		// find out which way is forward
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//		// get forward vector
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//		AddMovementInput(Direction, Value);
//	}
//}
//
//void ANeoSteamCharacter::MoveRight(float Value)
//{
//	if ( (Controller != NULL) && (Value != 0.0f) )
//	{
//		// find out which way is right
//		const FRotator Rotation = Controller->GetControlRotation();
//		const FRotator YawRotation(0, Rotation.Yaw, 0);
//	
//		// get right vector 
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//		// add movement in that direction
//		AddMovementInput(Direction, Value);
//	}
//}

void ANeoSteamCharacter::NSCreateAttackCollision(FVector StartPosition, FVector AttackPosition, float AttackRadius, ESkillDmg SkillType)
{
	FCollisionQueryParams Params(NAME_None, false, this);
	FVector StartVec = PositionLogic(StartPosition);
	FVector EndVec = PositionLogic(AttackPosition);
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectType;

	ANeoSteamPlayer* Player = Cast<ANeoSteamPlayer>(this);
	if (Player)
	{
		TraceObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	}

	ANeoSteamMonster* Monster = Cast<ANeoSteamMonster>(this);
	if (Monster)
	{
		TraceObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2)); //Character
	}

	// create a collision sphere
	FCollisionShape AttackSphereCollision = FCollisionShape::MakeSphere(AttackRadius);

	// draw collision sphere
	//DrawDebugSphere(GetWorld(), StartVec, AttackSphereCollision.GetSphereRadius(), 50, FColor::Red, true);
	//DrawDebugSphere(GetWorld(), EndVec, AttackSphereCollision.GetSphereRadius(), 50, FColor::Red, true);

	/* Sphere Trace */
	IsHit = GetWorld()->SweepMultiByObjectType(
		HitResult, 
		StartVec,
		EndVec,
		FQuat::Identity, 
		TraceObjectType, 
		AttackSphereCollision,
		Params);
	
	if (IsHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hit!"));
		for (auto it : HitResult)
		{
			if (it.Actor.IsValid())
			{
				NSHitActor(it, SkillType);
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UnHit!"));
	}
}

void ANeoSteamCharacter::NSHitActor(FHitResult OnHit, ESkillDmg SkillType)
{
	UNeoSteamGameInstance* NeoSteamGameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());
	AActor* HitActor = Cast<AActor>(OnHit.Actor.Get());

	bool IsDeath = NeoSteamGameInstance->GetBattleLogic()->Battle(this, HitActor, SkillType);

	if (IsDeath)
	{
		Execute_Death(HitActor);
	//	HitObject->
	}
	else
	{
		Execute_DamageHit(HitActor);
	}
}

FVector ANeoSteamCharacter::PositionLogic(FVector _Position)
{
	Position = (GetActorForwardVector() * _Position.X) + (GetActorRightVector() * _Position.Y)
		+ (GetActorUpVector() * _Position.Z) + GetActorLocation();

	return Position;
}


bool ANeoSteamCharacter::Attack_Implementation()
{
	return true;
}

bool ANeoSteamCharacter::DamageHit_Implementation()
{
	return true;
}

bool ANeoSteamCharacter::Death_Implementation()
{
	return true;
}

bool ANeoSteamCharacter::Dead_Implementation()
{
	return true;
}