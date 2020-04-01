// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle/PuzzleBase.h"
#include "TriWayPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API ATriWayPuzzle : public APuzzleBase
{
	GENERATED_BODY()

public:

	ATriWayPuzzle();

	UFUNCTION(BlueprintCallable)
		virtual void MiniGameClear() override;
};
