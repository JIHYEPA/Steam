// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumStruct.generated.h"

/**
 * 
 */
UENUM(Blueprintable)
enum class ESkillDmg : uint8
{
	E_Basic = 0,	
	E_Magenet,	
	E_StrongAttack,	
	E_WeakAttack,
	E_SkillDmg_Cnt
};

UENUM(Blueprintable)
enum class EMonster : uint8
{
	E_CuteRobot,
	E_Dron,
	E_QuadrupedRobot,
	E_SpiderRobot,
	E_SwordRobot,
	E_Monster_Cnt
};