// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:

		AMonsterAIController(const FObjectInitializer& ObjectInitializer);
		
		UBlackboardComponent* GetBlackboard();

protected:


	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

	// Reference to the AI's blackboard component.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class	UBlackboardComponent* BlackboardComponent;

	// The Behavior Tree Component used by this AI.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

};
