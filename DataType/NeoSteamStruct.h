// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeoSteamStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStatusD
{
	GENERATED_USTRUCT_BODY()

public:
	
	//최대 체력
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MaxHp;

	//현재 체력
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Hp;

	//최대 마나
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MaxMp;

	//현재 마나
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Mp;

	//체력 회복
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float HpRecovery;

	//체력 회복 시간
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float HpRecoveryTime;

	//마나 회복
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MpRecovery;

	//마나 회복 시간
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MpRecoveryTime;

	//이동속도
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MoveSpeed;

	//최대 이동속도
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MaxMoveSpeed;

	//공격력
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float AttackDamage;

	//방어력
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Defense;

	//크리티컬 확률
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float CriticalRatio;

	//크리티컬 데미지
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float CriticalDamage;
	
	//공격속도
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float AttackSpeed;

	//공격거리
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float AttackRange;

	//공격거리타입
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		bool AttackRangeType;
};