// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuzzleManager.generated.h"

class APuzzleBase;
class ADoorOpen;

/**
 * 
 */
UCLASS()
class NEOSTEAM_API UPuzzleManager : public UObject
{
	GENERATED_BODY()

public:
	//ADoorOpen* _FirstDoor, ADoorOpen* _SecondDoor, APuzzleBase* _PuzzleBase
	UFUNCTION(BlueprintCallable)
		void Init(AActor* _FirstDoor, AActor* _SecondDoor, AActor* _PuzzleBase);

	UFUNCTION(BlueprintCallable)
		APuzzleBase* GetPuzzleBase();

	UFUNCTION(BlueprintCallable)
		ADoorOpen* GetFirstDoor();

	UFUNCTION(BlueprintCallable)
		ADoorOpen* GetSecondDoor();

	UFUNCTION(BlueprintCallable)
		int32 GetDoorIndex();

	UFUNCTION(BlueprintCallable)
		void DoorIndexSetting();

private:

	UPROPERTY(VisibleAnywhere, Category = PuzzleTarget, meta = (AllowPrivateAccess = "true"))
		APuzzleBase* PuzzleBase;

	UPROPERTY(VisibleAnywhere, Category = PuzzleTarget, meta = (AllowPrivateAccess = "true"))
		ADoorOpen* FirstDoor;

	UPROPERTY(VisibleAnywhere, Category = PuzzleTarget, meta = (AllowPrivateAccess = "true"))
		ADoorOpen* SecondDoor;

	UPROPERTY(VisibleAnywhere, Category = PuzzleTarget, meta = (AllowPrivateAccess = "true"))
		int32 DoorIndex;
};
