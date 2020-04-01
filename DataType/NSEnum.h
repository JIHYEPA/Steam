#pragma once

#include "CoreMinimal.h"
#include "NSEnum.generated.h"

UENUM()
enum class ENSCharacterTable : uint8
{
	eNSCharacterTable_Asset,
	eNSCharacterTable_Info,
	eNSCharacterTable_Status,
	eNSCharacterTable_Cnt
};

UENUM()
enum class ENSPlayerAsset : uint8
{
	eNSPlayerAsset_AnimBlueprint,
	eNSPlayerAsset_Mesh1,
	eNSPlayerAsset_Mesh2,
	eNSPlayerAsset_Mesh3,
	eNSPlayerAsset_Weapon1,
	eNSPlayerAsset_Weapon2,
	eNSPlayerAsset_Weapon3,
	eNSPlayerAsset_Weapon4,
	eNSPlayerAsset_Cnt
};

UENUM()
enum class ENSPlayerAnim : uint8
{
	eNSPlayerAnim_StepForward,
	eNSPlayerAnim_StepBack,
	eNSPlayerAnim_StepRight,
	eNSPlayerAnim_StepLeft,
	eNSPlayerAnim_Hit,
	eNSPlayerAnim_Die,
	eNSPlayerAnim_WeaponEquip,
	eNSPlayerAnim_WeaponUnarm,
	eNSPlayerAnim_Attack,
	eNSPlayerAnim_AttackCombo,
	eNSPlayerAnim_AttackLast,
	eNSPlayerAnim_AttackSkill,
	eNSPlayerAnim_ChangeSkill,
	eNSPlayerAnim_RangeSkill,
	eNSPlayerAnim_MagnetSkill,
	eNSPlayerAnim_BuffSkill,
	eNSPlayerAnim_Cnt
};

UENUM()
enum class ENSMonsterAnim : uint8
{
	eNSMonsterAnim_Reaction,
	eNSMonsterAnim_Attack,
	eNSMonsterAnim_Skill,
	eNSMonsterAnim_Hit,
	eNSMonsterAnim_Dead,
	eNSMonsterAnim_Cnt
};

UENUM(Blueprintable)
enum class ENSCharacterID : uint8
{
	eNSCharacter_Gideon,
	eNSCharacter_Revenant,
	eNSCharacter_CuteRobot,
	eNSCharacter_Dron,
	eNSCharacter_SwordRobot,
	eNSCharacter_QuadrupedRobot,
	eNSCharacter_SpiderRobot,
	eNSCharacter_Drongo,
	eNSCharacter_Crunch,
	eNSCharacter_Cnt
};