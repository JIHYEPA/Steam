// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NSCharacterTable.generated.h"

USTRUCT(BlueprintType)
struct FNSCharacterMontageData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
		FSoftObjectPath MontageRef;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage")
		uint8 Priority;
};

USTRUCT(BlueprintType)
struct FNSCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath ReferencePath;

};


USTRUCT(BlueprintType)
struct FNSCharacterAssetData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath AssetTablePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath MontageTablePath;

};

USTRUCT(BlueprintType)
struct FNSCharacterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath AnimBlueprint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CollisionPreset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Ragdoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CapsuleHalfHeight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CapsuleRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath Mesh_Skin0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath Mesh_Skin1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath Mesh_Skin2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath Mesh_Skin3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSoftObjectPath MontageDataTable;
};


USTRUCT(BlueprintType)
struct FNSCharacterStatus : public FTableRowBase
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
