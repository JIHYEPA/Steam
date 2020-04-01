// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeoSteamStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStatusD
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