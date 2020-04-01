// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include  "Character/NSCharacterInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataType/NeoSteamStruct.h"
#include "BattleLogic/EnumStruct.h"
#include "DataType/NSEnum.h"
#include "DataType/NSCharacterTable.h"
#include "NeoSteamCharacter.generated.h"

class AnimInstance;

UCLASS(config=Game)
class ANeoSteamCharacter : public ACharacter, public INSCharacterInterface
{
	GENERATED_BODY()

	///** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	///** Follow camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* FollowCamera;

public:
	ANeoSteamCharacter(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintCallable)
	virtual	void Init(ENSCharacterID CharacterID);


	virtual void BeginPlay() override;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)Ʈ
	//float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	//float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	//void OnResetVR();

	///** Called for forwards/backward input */
	//void MoveForward(float Value);

	///** Called for side to side input */
	//void MoveRight(float Value);

	///** 
	// * Called via input to turn at a given rate. 
	// * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	// */
	//void TurnAtRate(float Rate);

	///**
	// * Called via input to turn look up/down at a given rat	e. 
	// * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	// */
	//void LookUpAtRate(float Rate);

	///** Handler for when a touch input begins. */
	//void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	///** Handler for when a touch input stops. */
	//void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	bool AddHealthPoint(float HealthPoint);

	UFUNCTION(BlueprintCallable)
		void NSCreateAttackCollision(FVector StartPosition, FVector AttackPosition, float AttackRadius, ESkillDmg SkillType);

	UFUNCTION(BlueprintCallable)
		void NSHitActor(FHitResult OnHit, ESkillDmg SkillType);
		
	FVector PositionLogic(FVector _Position);
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CharacterInterface")
		bool Attack();
	virtual bool Attack_Implementation() override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CharacterInterface")
		bool DamageHit();
	virtual bool DamageHit_Implementation() override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CharacterInterface")
		bool Death();
	virtual bool Death_Implementation() override;
	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CharacterInterface")
		bool Dead();
	virtual bool Dead_Implementation() override;

	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


public:
	
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Stat")
	FNSCharacterStatus Status;
	
	//State 
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool IsJump;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool IsAttack;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool IsSkill;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool IsMove;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool IsHit;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool IsDying;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool bPushTarget;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "State")
	bool bPushEnd;

public:

	class ULevelMontage* LevelMontage;

	TArray<UAnimMontage*> AnimMontages;

	TArray<FHitResult> HitResult;

	FVector Position;
	
	ENSCharacterID ID;
	//////////

};

