// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Manager/UIManager.h"
#include "Manager/CameraManager.h"
#include "Manager/PuzzleManager.h"
#include "DataType/NSCharacterTable.h"
#include "DataType/NSEnum.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NeoSteamGameInstance.generated.h"

class UBattleLogic;
class UPuzzleManager;
class UCharacterManager;
//class UCameraManager;
//class UUIManager;
//class ANeoSteamPlayer;

/**
 * 
 */

UCLASS(Config = Engine)
class NEOSTEAM_API UNeoSteamGameInstance : public UGameInstance
{
	GENERATED_BODY()
//
//	UFUNCTION(BlueprintCallable)
//		UCameraManager* GetCameraMgr();
//
	//UFUNCTION(BlueprintCallable)
	//	UUIManager* GetUIManager();
//
//	UFUNCTION(BlueprintCallable)
//		UUIManager* CreateUIManager();
//
private:
	UPROPERTY()
		UBattleLogic* BattleLogic;

	UPROPERTY()
		UPuzzleManager* PuzzleMgr;

	UPROPERTY()
		UCharacterManager* CharacterMgr;

	//UPROPERTY()
	//	UCameraManager* CameraMgr;
	
//
//	UPROPERTY()
//		ANeoSteamPlayer* Player
public:

	UNeoSteamGameInstance();

	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable)
		UBattleLogic* GetBattleLogic();

	UFUNCTION(BlueprintCallable)
		UPuzzleManager* GetPuzzleMgr();

	UFUNCTION(BlueprintCallable)
		UCharacterManager* GetCharacterMgr();


	UPROPERTY(Config)
		TArray<FSoftObjectPath> FNSCharacterMontageTableRef;

	const FNSCharacterMontageData& GetCharacterMontagetable(ENSCharacterID CharacterID, ENSMonsterAnim MonsterAnim);

	const FNSCharacterMontageData& GetCharacterMontagetable(ENSCharacterID CharacterID, ENSPlayerAnim PlayerAnim);
	
	const FNSCharacterStatus& GetCharacterStatusTable(ENSCharacterID CharacterID);

	const FNSCharacterInfo& GetCharacterInfo(ENSCharacterID CharacterID);

	void AsyncLoad();
			
	UDataTable* FNSCharacterStatusTable;
	UDataTable* FNSCharacterInfoTable;



};
