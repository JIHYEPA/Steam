// Fill out your copyright notice in the Description page of Project Settings.


#include "NeoSteamMonster.h"
#include "UObject/ConstructorHelpers.h"
#include "Character/LevelMontage.h"
#include "Components/MeshComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/Monster/AI/MonsterAIController.h"
#include "GamePlayFramework/NeoSteamGameInstance.h"
#include "Manager/CharacterManager.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"

ANeoSteamMonster::ANeoSteamMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> AICon(TEXT("/Game/Character/Monster/AI/AI_MonsterController.AI_MonsterController"));
	AIControllerClass = AICon.Object->GeneratedClass;

	//AIControllerClass = AMonsterAIController::StaticClass();
//	this->Controller
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationYaw = true;	
}

bool ANeoSteamMonster::Attack_Implementation()
{
	if (IsDying)
	{
		return true;
	}

	UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());

	LevelMontage->PlayAnimMontage(GameInstance->GetCharacterMontagetable(ID, ENSMonsterAnim::eNSMonsterAnim_Attack));

	return true;
}

bool ANeoSteamMonster::DamageHit_Implementation()
{
	if (IsDying)
	{
		return true;
	}

	UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());

	LevelMontage->PlayAnimMontage(GameInstance->GetCharacterMontagetable(ID, ENSMonsterAnim::eNSMonsterAnim_Hit));

	return true;
}

bool ANeoSteamMonster::Death_Implementation()
{
	if (IsDying)
	{
		return true;
	}

	UNeoSteamGameInstance* GameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());

	LevelMontage->PlayAnimMontage(GameInstance->GetCharacterMontagetable(ID, ENSMonsterAnim::eNSMonsterAnim_Dead));

	
	if (GameInstance->GetCharacterInfo(ID).Ragdoll)
	{
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));

		GetMesh()->SetSimulatePhysics(true);
	}

	IsDying = true;

	AAIController* AI = Cast<AAIController>(GetController());

	AI->GetBrainComponent()->StopLogic(TEXT("Delete"));
	
	GameInstance->GetCharacterMgr()->DeathMonster(this);
	   
	//Destroy();
	return true;
}

bool ANeoSteamMonster::Dead_Implementation()
{
	return true;
}