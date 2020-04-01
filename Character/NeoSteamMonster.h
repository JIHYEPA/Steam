// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeoSteamCharacter.h"
#include "NSCharacterInterface.h"
#include "NeoSteamMonster.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API ANeoSteamMonster : public ANeoSteamCharacter
{
	GENERATED_BODY()


public:

	ANeoSteamMonster(const FObjectInitializer& ObjectInitializer);
	
	virtual bool Attack_Implementation() override;

	virtual bool DamageHit_Implementation() override;

	virtual bool Death_Implementation() override;

	virtual bool Dead_Implementation() override;
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		int32 MinMoveDistance;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		int32 MaxMoveDistance;


	//class AAIController* AI
};
