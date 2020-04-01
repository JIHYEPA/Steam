// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NSAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API UNSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UNSAnimInstance();

	// the below functions are the native overrides for each phase
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;

	// Executed when begin play is called on the owning component
	virtual void NativeBeginPlay() override;

	//It is usually a good idea to simply gather data in this stepand
	// for the bulk of the work to be done in NativeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//character move bool
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	bool IsAccelerating;					  
											  
	//character jump state or drop			  
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	bool IsAir;								  
											  
	//character move speed					  
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	float MoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Action")
	bool bPushTarget;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Action")
	bool bPushEnd;
};
