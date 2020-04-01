// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterManager.generated.h"

class ASpawnActor;
class UNeoSteamGameInstance;
/**
 * 
 */
UCLASS()
class NEOSTEAM_API UCharacterManager : public UObject
{
	GENERATED_BODY()
	
public:

	UCharacterManager();

	virtual void BeginDestroy() override;

	void SetGameInstance(UNeoSteamGameInstance* GameInstance);

	UFUNCTION(BlueprintCallable)
		void Init(AActor* _SpawnActor);

	UFUNCTION(BlueprintCallable)
		void SpawnMonster(AActor* _Monster);

	UFUNCTION(BlueprintCallable)
		void DeathMonster(AActor* _Monster);

	void FirstDoorOpen();

public:

	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> MonsterArr;

	UPROPERTY(BlueprintReadWrite)
		ASpawnActor* SpawnActor;

private:

	UNeoSteamGameInstance* NSGameInstance;
};
