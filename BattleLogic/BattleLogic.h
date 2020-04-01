// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumStruct.h"
#include "BattleLogic.generated.h"

class ANeoSteamCharacter;
class ANeoSteamPlayer;
class ANeoSteamMonster;

/**
 * 
 */
UCLASS(Blueprintable)
class NEOSTEAM_API UBattleLogic : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		bool Battle(AActor* _Attacker, AActor* _Defenser, ESkillDmg SkillDmg);

	UFUNCTION(BlueprintImplementableEvent)
		void SkillEXPLogic(ANeoSteamPlayer* _Player, ANeoSteamMonster* _Monster);
	
	float DamageLogic(AActor* _Attacker, AActor* _Defenser);

	bool CriticalLogic(float CriticalRatio);

	float SkillDamageLogic(float Damage, ESkillDmg SkillDmg);

	bool MinusHP(float Damage, AActor* _Target);
};
