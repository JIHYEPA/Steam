// Fill out your copyright notice in the Description page of Project Settings.


#include "NeoSteamGameInstance.h"
#include "Engine/GameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "BattleLogic/BattleLogic.h"
#include "Manager/CharacterManager.h"
#include "Manager/CameraManager.h"
#include "Manager/PuzzleManager.h"
#include "Manager/UIManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "UObject/SoftObjectPtr.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

UNeoSteamGameInstance::UNeoSteamGameInstance()
{	
	FString NSCharacterStatusTablePath = TEXT("/Game/Table/NSCharacterStatusTable.NSCharacterStatusTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_NSCharacterStatusTable(*NSCharacterStatusTablePath);

	if (DT_NSCharacterStatusTable.Succeeded())
	{
		FNSCharacterStatusTable = DT_NSCharacterStatusTable.Object;
	}

	FString NSCharacterInfoTablePath = TEXT("/Game/Table/CharacterInfoTable.CharacterInfoTable");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_NSCharacterInfoTable(*NSCharacterInfoTablePath);

	if (DT_NSCharacterInfoTable.Succeeded())
	{
		FNSCharacterInfoTable = DT_NSCharacterInfoTable.Object;
	}

	/*for (int8 i = 0; i < (int8)ENSCharacterID::eNSCharacter_Cnt; ++i)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> DT_NSMontageTable(*GetCharacterInfo((ENSCharacterID)i).MontageDataTable.ToString());

		if (DT_NSMontageTable.Succeeded())
		{
			FNSCharacterMontageTable.Add(DT_NSMontageTable.Object);
		}
	}*/
}

void UNeoSteamGameInstance::Init()
{
	Super::Init();
	
	BattleLogic = NewObject<UBattleLogic>(UBattleLogic::StaticClass());
	PuzzleMgr = NewObject<UPuzzleManager>(UPuzzleManager::StaticClass());
	CharacterMgr = NewObject<UCharacterManager>(UCharacterManager::StaticClass());

	CharacterMgr->SetGameInstance(this);	
	
	auto& assetLoader = UAssetManager::GetStreamableManager();
	
	assetLoader.RequestAsyncLoad(FNSCharacterMontageTableRef[FNSCharacterMontageTableRef.Num() - 1],
		FStreamableDelegate::CreateUObject(this, &UNeoSteamGameInstance::AsyncLoad)
	);

	//for (int8 i = 0; i < (int8)ENSCharacterID::eNSCharacter_Cnt; ++i)
	//{
	//	UDataTable* DataTable = Cast<UDataTable>(GetCharacterInfo((ENSCharacterID)i).MontageDataTable.esolveObject());

	//	if (GetCharacterInfo((ENSCharacterID)i).MontageDataTable.IsNull())
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Fail Montage"));
	//	}

	//	if (DataTable == nullptr)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Fail DataTable"));
	//	}

	//	FNSCharacterMontageTable.Add(DataTable);
	//}		
}

const FNSCharacterMontageData& UNeoSteamGameInstance::GetCharacterMontagetable(ENSCharacterID CharacterID, ENSMonsterAnim MonsterAnim)
{
	UDataTable* Table = Cast<UDataTable>(FNSCharacterMontageTableRef[(uint8)CharacterID].TryLoad());

	auto Names = Table->GetRowNames();

	return *(Table->FindRow<FNSCharacterMontageData>(Names[(uint8)MonsterAnim], FString()));
}

const FNSCharacterMontageData& UNeoSteamGameInstance::GetCharacterMontagetable(ENSCharacterID CharacterID, ENSPlayerAnim PlayerAnim)
{
	UDataTable* Table = Cast<UDataTable>(FNSCharacterMontageTableRef[(uint8)CharacterID].TryLoad());

	auto Names = Table->GetRowNames();

	return *(Table->FindRow<FNSCharacterMontageData>(Names[(uint8)PlayerAnim], FString()));
}
//
//
//const FNSCharacterMontageData& UNeoSteamGameInstance::GetCharacterMontagetable(ENSCharacterID CharacterID, ENSMonsterAnim MonsterAnim)
//{
//	auto Names = FNSCharacterMontageTable[(uint8)CharacterID]->GetRowNames();
//	
//	return *(FNSCharacterMontageTable[(uint8)CharacterID]->FindRow<FNSCharacterMontageData>(Names[(uint8)MonsterAnim], FString()));
//}
//
//const FNSCharacterMontageData& UNeoSteamGameInstance::GetCharacterMontagetable(ENSCharacterID CharacterID, ENSPlayerAnim PlayerAnim)
//{
//	auto Names = FNSCharacterMontageTable[(uint8)CharacterID]->GetRowNames();
//
//	return *(FNSCharacterMontageTable[(uint8)CharacterID]->FindRow<FNSCharacterMontageData>(Names[(uint8)PlayerAnim], FString()));
//}

const FNSCharacterStatus& UNeoSteamGameInstance::GetCharacterStatusTable(ENSCharacterID CharacterID)
{
	auto Names = FNSCharacterStatusTable->GetRowNames();
	
	return *(FNSCharacterStatusTable->FindRow<FNSCharacterStatus>(Names[(uint8)CharacterID], FString()));
}

const FNSCharacterInfo& UNeoSteamGameInstance::GetCharacterInfo(ENSCharacterID CharacterID)
{
	auto Names = FNSCharacterInfoTable->GetRowNames();
	
	return *(FNSCharacterInfoTable->FindRow<FNSCharacterInfo>(Names[(uint8)CharacterID], FString()));
}

void UNeoSteamGameInstance::AsyncLoad()
{
	//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("DataTable Num : %d"), FNSCharacterMontageTableRef.Num()));

	for (int32 i = 0; i < FNSCharacterMontageTableRef.Num(); ++i)
	{
		if (FNSCharacterMontageTableRef[i] == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("Fail DataTable"));
		}
	}

}

UBattleLogic* UNeoSteamGameInstance::GetBattleLogic()
{
	return BattleLogic;
}

UPuzzleManager* UNeoSteamGameInstance::GetPuzzleMgr()
{
	return PuzzleMgr;
}

UCharacterManager* UNeoSteamGameInstance::GetCharacterMgr()
{
	return CharacterMgr;
}

//UCameraManager* UNeoSteamGameInstance::GetCameraMgr()
//{
//	return CameraMgr;
//}
//
//
//UUIManager* UNeoSteamGameInstance::CreateUIManager()
//{
//	UIMgr = NewObject<UUIManager>(UUIManager::StaticClass());
//
//	//UI À§Á¬ »ý¼º
//
//	return UIMgr;
//


