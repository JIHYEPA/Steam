// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HUD_PlayerLayout.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API UHUD_PlayerLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init();

	UFUNCTION(BlueprintCallable)
	void ShowInteractionText(FString InterText);

	UFUNCTION(BlueprintCallable)
	void EndInteractionText();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* InterfaceText;
};
