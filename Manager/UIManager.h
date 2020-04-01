// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HUD/HUD_PlayerLayout.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "UIManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NEOSTEAM_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:
	UUIManager();

	UFUNCTION()
		void Init();
public:

	//Reference UMG Asset in the Editor
	//UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Widgets")
	//	TSubclassOf<UUserWidget> wMultiPlayMenu;

	//UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Widgets")
	//	TSubclassOf<UUserWidget> wUserWidget;

	//UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Widgets")
	//	UHUD_PlayerLayout* wMultiPlayMenu;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Widgets")
		TSubclassOf<UHUD_PlayerLayout> WidgetClass;

	UPROPERTY()
		UHUD_PlayerLayout* WidgetInstance;
};
