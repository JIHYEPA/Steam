// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLogic.h"
#include "NeoSteamCharacter.h"
#include "./Character/NeoSteamPlayer.h"
#include "./Character/NeoSteamMonster.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Math/RandomStream.h"

bool UBattleLogic::Battle(AActor* _Attacker, AActor* _Defenser, ESkillDmg SkillDmg)
{
	if (_Attacker == nullptr || _Defenser == nullptr)
	{
		return false;
	}
	ANeoSteamCharacter* Attacker = Cast<ANeoSteamCharacter>(_Attacker);
	ANeoSteamCharacter* Defenser = Cast<ANeoSteamCharacter>(_Defenser);
	
	if(Attacker == nullptr || Defenser == nullptr)
	{
		return false;
	}

	float Damage = DamageLogic(Attacker, Defenser);

	Damage = SkillDamageLogic(Damage, SkillDmg);

	bool IsDeath = MinusHP(Damage, Defenser);

	ANeoSteamPlayer* player = Cast<ANeoSteamPlayer>(Attacker);
	ANeoSteamMonster* monster = Cast<ANeoSteamMonster>(Defenser);
	if (player && monster) // Cast != nullptr
	{
		SkillEXPLogic(player, monster);
	}

	return IsDeath;
}

float UBattleLogic::DamageLogic(AActor* _Attacker, AActor* _Defenser)
{
	ANeoSteamCharacter* Attacker = Cast<ANeoSteamCharacter>(_Attacker);
	ANeoSteamCharacter* Defenser = Cast<ANeoSteamCharacter>(_Defenser);

	float AttackDmg = Attacker->Status.AttackDamage;
	float CriticalDmg = Attacker->Status.CriticalDamage;
	float Defense = Defenser->Status.Defense;

	float DamageLg = (AttackDmg * CriticalDmg) - Defense;
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hit %s Damage : %f"), *Defenser->GetName(), DamageLg));

	if (DamageLg <= 0)
	{
		return 1;
	}
	else
	{
		if (CriticalLogic(Attacker->Status.CriticalRatio))
		{
			return DamageLg;
		}
		else
		{
			return AttackDmg - Defense;
		}
	}
}

bool UBattleLogic::CriticalLogic(float CriticalRatio)
{
	if (FMath::RandRange(1, 100) <= (CriticalRatio * 100))
	{
		return true;
	}
	return false;
}

float UBattleLogic::SkillDamageLogic(float Damage, ESkillDmg SkillDmg)
{
	float SkillDmgRatio = 0;

	switch (SkillDmg)
	{
	case ESkillDmg::E_Basic:
		return Damage;
		break;
	case ESkillDmg::E_Magenet:
		SkillDmgRatio = 0.0001;
		break;
	case ESkillDmg::E_StrongAttack:
		SkillDmgRatio = 3;
		break;
	case ESkillDmg::E_WeakAttack:
		SkillDmgRatio = 1.5;
		break;
	}

	if (SkillDmgRatio != 0)
	{
		return Damage * SkillDmgRatio;
	}

	return Damage;
}

bool UBattleLogic::MinusHP(float Damage, AActor* _Target)
{
	if (_Target == nullptr)
	{
		return false;
	}

	ANeoSteamCharacter* Target = Cast<ANeoSteamCharacter>(_Target);
	if (Target == nullptr)
	{
		return false;
	}

	return !Target->AddHealthPoint(-Damage);	
}
