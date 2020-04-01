// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Interaction/InterfaceActor.h"
#include "NeoSteamGameMode.h"
#include "CoreMinimal.h"
#include "NeoSteamCharacter.h"
#include "BattleLogic/EnumStruct.h"
#include "DataType/NSEnum.h"
#include "DataType/NSCharacterTable.h"
#include "NSCharacterInterface.h"
#include "Animation/AnimInstance.h"
#include "NeoSteamPlayer.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPushMode, AActor*, PushObject, bool, OverlapObject);



class USceneComponent;
class UBoxComponent;

UCLASS()
class NEOSTEAM_API ANeoSteamPlayer : public ANeoSteamCharacter
{
	GENERATED_BODY()

public:
	ANeoSteamPlayer(const FObjectInitializer& ObjectInitializer);


	virtual void Init(ENSCharacterID CharacterID);

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Player Move
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);
		   	   
	void NSMagnetAction(FVector StartPosition, FVector AttackPosition, float AttackRadius, ESkillDmg SkillType);

	void NSSpawnMagnetEmitter(FVector _Position);

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void onTimerEnd();

	/*void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);*/

public:

	//Character Battle Interface
	virtual bool Attack_Implementation() override;

	virtual bool DamageHit_Implementation() override;

	virtual bool Death_Implementation() override;

	virtual bool Dead_Implementation() override;
	//Common Attack
	void Attack();

	void ComboAttack();

	UFUNCTION(BlueprintCallable)
	void SaveComboAttack();
	
	UFUNCTION(BlueprintCallable)
	void ResetComboAttack();

	UFUNCTION()
	void AttackStateReset(UAnimMontage* AnimMontage, bool bInterrupted);

	//Player Mode Change
	UFUNCTION()
	void ChangeCharacterMode();

	UFUNCTION()
	void ChangeModeScene();

	UFUNCTION()
	void ChangeWeaponScene(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UFUNCTION()
		void EquipEnded(UAnimMontage* AnimMontage, bool bInterrupted);

	//Montage Interrupt
	void AttackInterrupt(UAnimMontage* AnimMontage, bool bInterrupted);

	UFUNCTION()
	void MoveStep(ENSPlayerAnim Step);

	UFUNCTION()
	void MoveStepEnded(UAnimMontage* AnimMontage, bool bInterrupted);
	
	void MoveObject(float AxisValue);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	void PushMode(UBoxComponent* Object, FVector Offset, bool OverlapObject);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	void PushEnd();

	FVector GetPushTargetLocation();

	UFUNCTION(BlueprintCallable, Category = Action)
	bool IsPushObject();

//	bool StateCheck(

//hong's
public:
	UCameraComponent* MainCamera;

	ANeoSteamGameMode* MyGameMode;


	UFUNCTION()
		AActor* GetInteractionActor();

	UFUNCTION()
		void GetInteractActorFocus();

	UPROPERTY()
		AInterfaceActor* LastInteractionActor;

		void Interaction();

	//For Interaction Network Replicated
	UFUNCTION(Server,Reliable,WithValidation)
	void OnServer();
	void OnServer_Implementation();
	bool OnServer_Validate();

	UFUNCTION(NetMulticast,Reliable,WithValidation)
	void OnMulticast();
	void OnMulticast_Implementation();
	bool OnMulticast_Validate();

	bool IsNewFocus;
		   	  
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Action")
	bool bOnPush;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Action")
	bool bPushMove;


protected:
	
	//Montage delegate
	FOnMontageEnded					MontageEnded;
	FOnMontageBlendingOutStarted	MontageStarted;

	UPROPERTY(BlueprintAssignable)
		FOnPushMode						OnPushMode;

	UBoxComponent* PushObjectCollision;
	
	//Attack Combo State

	/* ComboAttack Check */
	bool bAttacking;
	bool bSaveAttack;
	int32 AttackCount;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Action")
	bool bPlayerMode;

	bool bEquip;

	bool bAttack;
	bool bStep;
	bool bStepPressed;

	bool IsLadder;

	bool IsParticle;

	float MaxStamina;
	float Stamina;
	float StaminaRecoveryTime;

	UParticleSystem* MagnetFX;

	FTimerHandle _loopTimerHandle;

	float CountdownTime = 0.5f;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Scene")
	USceneComponent* CommonSceneComp;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Scene")
	USceneComponent* BattleSceneComp;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Scene")
	UStaticMeshComponent* Imsi;


	//TArray<UAnimMontage*> PlayerMontages;
};