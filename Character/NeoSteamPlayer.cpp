// Fill out your copyright notice in the Description page of Project Settings.


#include "NeoSteamPlayer.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "NeoSteamGameMode.h"
#include "HUD/NeoSteamHUD.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Animation/AnimBlueprint.h"
#include "Interaction/Interaction_Interface.h"
#include "GamePlayFramework/NeoSteamGameInstance.h"
#include "Character/LevelMontage.h"
#include "Components/MeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Vector.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Components/StaticMeshComponent.h"
#include "NSPlayerController.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathVectorCommon.h"



//#include "Math/UnrealMathUtility.h"

ANeoSteamPlayer::ANeoSteamPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bAttacking(false), bSaveAttack(false), AttackCount(0)
{
	PrimaryActorTick.bCanEverTick = true;
	bPushMove = false;
	bPlayerMode = true;

	bReplicates = true;
	//Player Mode Change SceneComponent
	CommonSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("CommonScene"));
	CommonSceneComp->SetupAttachment(RootComponent);
	BattleSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("BattleScene"));
	BattleSceneComp->SetupAttachment(RootComponent);


	Imsi = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));

	//BattleSceneComp->AttachToComponent(GetMesh(), Rule, FName(TEXT("Weapon_Socket")));
	//CommonSceneComp->AttachToComponent(GetMesh(), Rule, FName(TEXT("WeaponBase")));

	//// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->ProbeChannel = ECC_GameTraceChannel6;

	//// Create a follow camera
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	MainCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	MainCamera->SetRelativeLocationAndRotation(FVector(-56.f, 0.f, 185), FQuat(FRotator(-20.f, 0.f, 0.f)));
	MainCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	MainCamera->SetRelativeLocationAndRotation(FVector(-56.f, 0.f, 185), FRotator(-20.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> Weapon(TEXT("/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Sword.SM_Sword"));
	Imsi->SetStaticMesh(Weapon.Object);
	//Imsi = Weapon.Object;
	Imsi->SetupAttachment(CommonSceneComp);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MagnetParicle(TEXT("/Game/FXVarietyPack/Particles/P_magnet_Attract"));
	//MagnetFX = MagnetParicle.Object;

	
}

void ANeoSteamPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//현재 raycast 객체를 틱단위로 받아온다.
	GetInteractActorFocus();
}

AActor* ANeoSteamPlayer::GetInteractionActor()
{
	FHitResult OutHit;

	FCollisionQueryParams CollisionParams;

	//자기 자신은 무시한다.
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bTraceComplex = true;

	FVector Start = MainCamera->GetComponentLocation();

	FRotator CamRot = MainCamera->GetComponentRotation();


	FRotator CamRotXVector = MainCamera->GetComponentRotation();

	float Distance = CameraBoom->TargetArmLength + 300.0f;

	FVector CamForwardVec = MainCamera->GetForwardVector();
	FVector End = Start + (CamForwardVec * Distance);


	//DrawDebugLine(GetWorld(), Start, End, FColor(255, 0, 0), false, 1, 0, 1);

	//LineTrace 충돌 검사
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, ECC_WorldStatic, CollisionParams))
	{
		//받아온 객체가 그 interface를 상속받는지 
		if (OutHit.GetActor()->GetClass()->ImplementsInterface(UInteraction_Interface::StaticClass()))
		{
			//이 충돌한 객체를 반환
			return OutHit.GetActor();
		}
	}
	return nullptr;
}

void ANeoSteamPlayer::GetInteractActorFocus()
{
	AActor* InteractionActor = GetInteractionActor();

	ANSPlayerController* PlayerController = Cast<ANSPlayerController>(Controller);

	if (InteractionActor != LastInteractionActor)
	{
		IsNewFocus = true;

		if (IsValid(LastInteractionActor))
		{
			LastInteractionActor->EndOutlineFocus();

			if (PlayerController != nullptr)
			{
				PlayerController->MyMainMenu->EndInteractionText();
			}

			LastInteractionActor = nullptr;
		}
	}

	if (IsValid(InteractionActor))
	{
		LastInteractionActor = Cast<AInterfaceActor>(InteractionActor);

		if (IsNewFocus)
		{
			if (!LastInteractionActor->GetIsUsed() && LastInteractionActor != nullptr && PlayerController != nullptr)
			{
				LastInteractionActor->BeginOutlineFocus();
				PlayerController->MyMainMenu->ShowInteractionText(LastInteractionActor->GetInteractionText());
				IsNewFocus = false;
			}
		}
	}
}

void ANeoSteamPlayer::Interaction()
{
	OnServer();
}

void ANeoSteamPlayer::OnServer_Implementation()
{
	OnMulticast();
}

bool ANeoSteamPlayer::OnServer_Validate()
{
	return true;
}

void ANeoSteamPlayer::OnMulticast_Implementation()
{
	AInterfaceActor* InterfaceActor = Cast<AInterfaceActor>(GetInteractionActor());

	//InterfaceActor가 사용되지 않은 경우
	if (InterfaceActor != nullptr && InterfaceActor->GetIsUsed() == false)
	{
		ANSPlayerController* PlayerController = Cast<ANSPlayerController>(Controller);
		if (IsValid(PlayerController))
		{
			PlayerController->MyMainMenu->EndInteractionText();

			//상호작용 실행
			InterfaceActor->Interact(PlayerController);
		}
	}
}

bool ANeoSteamPlayer::OnMulticast_Validate()
{
	return true;
}



void ANeoSteamPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void ANeoSteamPlayer::Init(ENSCharacterID CharacterID)
{
	Super::Init(CharacterID);
	
	ID = CharacterID;

	this->bUseControllerRotationYaw = false;
	UCharacterMovementComponent* Move = GetCharacterMovement();
	if (Move != nullptr)
	{
		Move->bOrientRotationToMovement = true;
		Move->SetWalkableFloorAngle(55.f);
	}

	bPlayerMode = false;

	USkeletalMeshComponent* WeaponSocket = GetMesh();

	FAttachmentTransformRules Rule(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	BattleSceneComp->AttachToComponent(WeaponSocket, Rule, TEXT("Weapon_Socket"));
	CommonSceneComp->AttachToComponent(WeaponSocket, Rule, TEXT("WeaponBase"));

	//BattleSceneComp->AttachToComponent(GetMesh(), Rule, FName(TEXT("Weapon_Socket")));
	//CommonSceneComp->AttachToComponent(GetMesh(), Rule, FName(TEXT("WeaponBase")));
	
	CommonSceneComp->SetRelativeLocation(FVector(-13.f, 0.f, 36.f));
	CommonSceneComp->SetRelativeRotation(FRotator(20.f, 0.f, 0.f));

	BattleSceneComp->SetRelativeLocation(FVector(8.f, 3.7f, -17.f));
	BattleSceneComp->SetRelativeRotation(FRotator(190.f, 0.f, 5.f));

}

void ANeoSteamPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ANeoSteamPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);/*
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);*/

	PlayerInputComponent->BindAxis("MoveForward", this, &ANeoSteamPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANeoSteamPlayer::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &ANeoSteamPlayer::Attack);
	PlayerInputComponent->BindAction("WeaponEquip", IE_Pressed, this, &ANeoSteamPlayer::ChangeCharacterMode);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ANeoSteamPlayer::Interaction);
	PlayerInputComponent->BindAction("ObjectPushEnd", IE_Pressed, this, &ANeoSteamPlayer::PushEnd);

}

void ANeoSteamPlayer::MoveForward(float AxisValue)
{
	if (AxisValue != 0.0f && !IsDying)
	{
		FRotator Rotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);

		if (bPushMove && bPushTarget && AxisValue < 0.f)
		{
		}
		else
		{
			if (bPushMove)
			{
				MoveObject(AxisValue);
			}
			else
			{
				if (!bPushTarget && !bOnPush)
				{
					AddMovementInput(FRotationMatrix(Rotation).GetUnitAxis(EAxis::X), AxisValue);
				}
			}
		}

		ANSPlayerController* PlayerController = Cast<ANSPlayerController>(Controller);

		if (PlayerController != nullptr)
		{
			if (PlayerController->IsInputKeyDown(EKeys::LeftShift) && bPlayerMode && !bPushTarget)
			{
				if (AxisValue >= 0.f)
				{
					MoveStep(ENSPlayerAnim::eNSPlayerAnim_StepForward);
				}
				else
				{
					MoveStep(ENSPlayerAnim::eNSPlayerAnim_StepBack);
				}
			}
		}
	}
}

void ANeoSteamPlayer::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f && !IsDying && !bPushTarget)
	{
		FRotator Rotation = FRotator(0, GetControlRotation().Yaw, 0);

		if (!bPushTarget && !bOnPush)
		{
			AddMovementInput(FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y), AxisValue);
					   			 
			ANSPlayerController* PlayerController = Cast<ANSPlayerController>(Controller);

			if (PlayerController != nullptr)
			{
				if (PlayerController->IsInputKeyDown(EKeys::LeftShift) && bPlayerMode)
				{
					if (AxisValue > 0.f)
					{
						MoveStep(ENSPlayerAnim::eNSPlayerAnim_StepRight);
					}
					else
					{
						MoveStep(ENSPlayerAnim::eNSPlayerAnim_StepLeft);
					}
				}
			}
		}
	}
}

void ANeoSteamPlayer::Attack()
{
	if (bPlayerMode)
	{
		Attack_Implementation();
	}
}

bool ANeoSteamPlayer::Attack_Implementation()
{
	if (bAttacking)
	{
		bSaveAttack = true;
	}
	else
	{
		bAttacking = true;

		ComboAttack();
	}

	return true;
}

void ANeoSteamPlayer::ComboAttack()
{
	UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());
	FNSCharacterMontageData MontageData;
	bool PlayMontage = false;

	if (GameInstance != nullptr)
	{
		switch (AttackCount)
		{
		case 0:
			++AttackCount;
			MontageData = GameInstance->GetCharacterMontagetable(ID, ENSPlayerAnim::eNSPlayerAnim_Attack);
			break;
		case 1:
			++AttackCount;
			MontageData = GameInstance->GetCharacterMontagetable(ID, ENSPlayerAnim::eNSPlayerAnim_AttackCombo);
			break;
		case 2:
			AttackCount = 0;
			MontageData = GameInstance->GetCharacterMontagetable(ID, ENSPlayerAnim::eNSPlayerAnim_AttackLast);
			break;
		}

		if (LevelMontage->PlayAnimMontage(MontageData))
		{
			MontageStarted.BindUObject(this, &ANeoSteamPlayer::AttackInterrupt);
			GetMesh()->GetAnimInstance()->Montage_SetBlendingOutDelegate(MontageStarted, Cast<UAnimMontage>(MontageData.MontageRef.TryLoad()));
		}
		else
		{
			ResetComboAttack();
		}
	}
}

void ANeoSteamPlayer::SaveComboAttack()
{
	if (bSaveAttack)
	{
		bSaveAttack = false;

		ComboAttack();
	}
}

void ANeoSteamPlayer::ResetComboAttack()
{
	bSaveAttack = false;
	bAttacking = false;
	AttackCount = 0;
}

void ANeoSteamPlayer::AttackStateReset(UAnimMontage* AnimMontage, bool bInterrupted)
{
	bAttack = false;

	if (bInterrupted)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Attack Montage Start Interrupted"));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Attack Montage Start"));
	}
}

void ANeoSteamPlayer::ChangeCharacterMode()
{
	UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());
	FNSCharacterMontageData MontageData;
	 
	if (!bEquip && !bAttacking &!bPushTarget)
	{
		if (!bPlayerMode)
		{
			MontageData = GameInstance->GetCharacterMontagetable(ID, ENSPlayerAnim::eNSPlayerAnim_WeaponEquip);
		}
		else
		{
			MontageData = GameInstance->GetCharacterMontagetable(ID, ENSPlayerAnim::eNSPlayerAnim_WeaponUnarm);
		}

		if (LevelMontage->PlayAnimMontage(MontageData))
		{
			bEquip = true;
			MontageStarted.BindUObject(this, &ANeoSteamPlayer::EquipEnded);
			GetMesh()->GetAnimInstance()->Montage_SetBlendingOutDelegate(MontageStarted, Cast<UAnimMontage>(MontageData.MontageRef.TryLoad()));
		}

		bUseControllerRotationYaw = !bUseControllerRotationYaw;

		bPlayerMode = !bPlayerMode;
	}
}

void ANeoSteamPlayer::ChangeModeScene()
{
	UCharacterMovementComponent* Move = GetCharacterMovement();
	FAttachmentTransformRules ATR(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);

	if (!bPushTarget)
	{
		if (bPlayerMode)
		{
			Imsi->AttachToComponent(BattleSceneComp, ATR);
			Move->bOrientRotationToMovement = false;
		}
		else
		{
			Imsi->AttachToComponent(CommonSceneComp, ATR);
			Move->bOrientRotationToMovement = true;
		}
	}
}

void ANeoSteamPlayer::ChangeWeaponScene(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("notify name : %s"), *NotifyName.ToString()));
}

void ANeoSteamPlayer::EquipEnded(UAnimMontage* AnimMontage, bool bInterrupted)
{
	bEquip = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Equip End"));
}

void ANeoSteamPlayer::AttackInterrupt(UAnimMontage* AnimMontage, bool bInterrupted)
{
	if (AnimMontage != nullptr)
	{
		if (bInterrupted && bStep)
		{
			ResetComboAttack();
		}

		bAttack = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Attack Montage End"));
	}
}

void ANeoSteamPlayer::MoveStep(ENSPlayerAnim Step)
{
	if (!bStep)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Step"));

		UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());

		if (GameInstance != nullptr)
		{
			FNSCharacterMontageData MontageData = GameInstance->GetCharacterMontagetable(ID, Step);

			bStep = true;

			if (LevelMontage->PlayAnimMontage(MontageData))
			{
				MontageStarted.BindUObject(this, &ANeoSteamPlayer::MoveStepEnded);
				GetMesh()->GetAnimInstance()->Montage_SetBlendingOutDelegate(MontageStarted, Cast<UAnimMontage>(MontageData.MontageRef.TryLoad()));
			}
			else
			{
				bStep = false;
			}
		}
	}
}

void ANeoSteamPlayer::MoveStepEnded(UAnimMontage* AnimMontage, bool bInterrupted)
{
	bStep = false;
}

void ANeoSteamPlayer::MoveObject(float AxisValue)
{
	if (bOnPush && PushObjectCollision != nullptr)
	{
		//PushObject->
		AActor* Object = PushObjectCollision->GetOwner();

		if (Object != nullptr)
		{
			FRotator Rotation = FRotator(0.f, GetActorRotation().Yaw, 0.f);
			FVector PushTargetLocation = GetPushTargetLocation();
			FVector ObjectLocation;

			PushTargetLocation.Z = Object->GetActorLocation().Z;

			ObjectLocation = FMath::VInterpTo(Object->GetActorLocation(), PushTargetLocation, GetWorld()->GetDeltaSeconds(), 200.f);

			Object->SetActorLocation(PushTargetLocation);

			AddMovementInput(FRotationMatrix(Rotation).GetUnitAxis(EAxis::X), AxisValue);
		}
	}
}

void ANeoSteamPlayer::PushMode(UBoxComponent* Object, FVector Offset, bool OverlapObject)
{
	if (Object != nullptr)
	{
		if (!OverlapObject && !(PushObjectCollision != nullptr))
		{
			PushEnd();
		}
		else
		{
			PushObjectCollision = Object;
			bPushTarget = bOnPush = OverlapObject;
		}
	}
}

void ANeoSteamPlayer::PushEnd()
{
	if (PushObjectCollision != nullptr && bPushTarget)
	{
		bPushEnd = true;
		bPushTarget = false;
		bPushMove = false;
		PushObjectCollision = nullptr;
	}
}

FVector ANeoSteamPlayer::GetPushTargetLocation()
{
	if (PushObjectCollision != nullptr)
	{
		return (PushObjectCollision->GetScaledBoxExtent() + 70.f) * GetActorForwardVector() + GetActorLocation();
	}

	return FVector();
}

bool ANeoSteamPlayer::IsPushObject()
{
	if (PushObjectCollision == nullptr)
	{
		return true;
	}
	return false;
}

bool ANeoSteamPlayer::DamageHit_Implementation()
{
	if (!IsDying && !bAttacking)
	{
		UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());

		if (GameInstance != nullptr)
		{
			LevelMontage->PlayAnimMontage(GameInstance->GetCharacterMontagetable(ID, ENSPlayerAnim::eNSPlayerAnim_Hit));
		}
	}
	return true;
}

bool ANeoSteamPlayer::Death_Implementation()
{
	if (IsDying)
	{
		return true;
	}

	UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());

	if (GameInstance != nullptr)
	{
		if (LevelMontage->PlayAnimMontage(GameInstance->GetCharacterMontagetable(ID, ENSPlayerAnim::eNSPlayerAnim_Die)))
		{
			IsDying = true;
		}
	}

	return true;
}

bool ANeoSteamPlayer::Dead_Implementation()
{
	return true;
}


void ANeoSteamPlayer::NSMagnetAction(FVector StartPosition, FVector AttackPosition, float AttackRadius, ESkillDmg SkillType)
{
	NSCreateAttackCollision(StartPosition, AttackPosition, AttackRadius, SkillType);

	if (IsHit)
	{
		for (auto it : HitResult)
		{
			if (it.Actor.IsValid())
			{
				ANeoSteamCharacter* HitCharacter = Cast<ANeoSteamCharacter>(it.Actor.Get());
				HitCharacter->SetActorLocation(Position);

				if (!IsParticle)
				{
					NSSpawnMagnetEmitter(Position);
				}
			}
		}
	}
}

void ANeoSteamPlayer::NSSpawnMagnetEmitter(FVector _Position)
{
	if (MagnetFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			MagnetFX,
			_Position);

		IsParticle = true;

		GetWorldTimerManager().SetTimer(_loopTimerHandle, this, &ANeoSteamPlayer::onTimerEnd, CountdownTime, false);
	}
}

void ANeoSteamPlayer::onTimerEnd()
{
	--CountdownTime;
	if (CountdownTime < 1) //TimeOut
	{
		GetWorldTimerManager().ClearTimer(_loopTimerHandle); //Timer Stop

		MagnetFX->FinishDestroy();

		IsParticle = false;
	}
}