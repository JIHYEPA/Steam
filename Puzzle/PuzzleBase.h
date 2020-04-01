// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InterfaceActor.h"
#include "PuzzleBase.generated.h"

//MultiCast
DECLARE_MULTICAST_DELEGATE(FOpen);

/**
 * 
 */
UCLASS()
class NEOSTEAM_API APuzzleBase : public AInterfaceActor
{
	GENERATED_BODY()
	
protected:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	APuzzleBase();

	virtual bool Interact_Implementation(APlayerController* playercontroller) override;

	virtual void MiniGameClear();

	FOpen FDele_Open;

public:

	UPROPERTY(BlueprintReadWrite)
		bool IsSuccessed;
};
