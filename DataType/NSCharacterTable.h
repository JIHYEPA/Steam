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

	//�ִ� ü��
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MaxHp;

	//���� ü��
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Hp;

	//�ִ� ����
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MaxMp;

	//���� ����
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Mp;

	//ü�� ȸ��
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float HpRecovery;

	//ü�� ȸ�� �ð�
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float HpRecoveryTime;

	//���� ȸ��
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MpRecovery;

	//���� ȸ�� �ð�
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MpRecoveryTime;

	//�̵��ӵ�
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MoveSpeed;

	//�ִ� �̵��ӵ�
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float MaxMoveSpeed;

	//���ݷ�
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float AttackDamage;

	//����
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float Defense;

	//ũ��Ƽ�� Ȯ��
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float CriticalRatio;

	//ũ��Ƽ�� ������
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float CriticalDamage;

	//���ݼӵ�
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float AttackSpeed;

	//���ݰŸ�
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		float AttackRange;

	//���ݰŸ�Ÿ��
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
		bool AttackRangeType;
};
