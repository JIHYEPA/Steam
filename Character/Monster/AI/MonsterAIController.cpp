// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Character/NeoSteamMonster.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AMonsterAIController::AMonsterAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("EnemyAIBlackboard"));
	BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("EnemyAIBehaviorTree"));
	////bWantsPlayerState = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObj(TEXT("/Game/Character/Monster/AI/BT_Monster.BT_Monster"));
	if (BehaviorTreeObj.Succeeded())
	{
		BehaviorTree = BehaviorTreeObj.Object;
	}
}

UBlackboardComponent* AMonsterAIController::GetBlackboard()
{
	return BlackboardComponent;
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
		
	if (BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*BehaviorTree, EBTExecutionMode::Looped);
	}	
}

void AMonsterAIController::OnUnPossess()
{
	BehaviorTreeComponent->StopTree();
}
