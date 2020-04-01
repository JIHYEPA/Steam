// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataType/NSCharacterTable.h"
#include "Animation/AnimMontage.h"
#include "LevelMontage.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEOSTEAM_API ULevelMontage : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULevelMontage();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	   	 
	bool PlayAnimMontage(FNSCharacterMontageData MontageData);

	void EndAnimMontage(UAnimMontage* AnimMontage, bool bInterrupted);

	void StopAnimMontage();

	uint8 PlayingPriority;

	bool bPlayMontage;

	FOnMontageEnded		MontageEnded;
		
};
