// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "HUD/HUD_PlayerLayout.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

UUIManager::UUIManager()
{
	/*ConstructorHelpers::FClassFinder<UHUD_PlayerLayout> MyWidget(TEXT("/Game/HUD/HUD_MyPlayerLayout.HUD_MyPlayerLayout"));
	if (MyWidget.Class)
	{
		WidgetClass = MyWidget.Class;
		WidgetInstance = CreateWidget<UHUD_PlayerLayout>(GetWorld(), WidgetClass);
	}*/
	//FStringClassReference MyWidgetClassRef(TEXT("/Game/HUD/NewBlueprint.NewBlueprint"));
	//if (UClass * MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
	//{ 
	//	wUserWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
	//	wMultiPlayMenu = Cast<UHUD_PlayerLayout>(wUserWidget);
	//}

	//static ConstructorHelpers::FClassFinder<UUserWidget> MyWidgetFinder(TEXT("/Game/HUD/HUD_MyPlayerLayout.HUD_MyPlayerLayout"));
	//if (MyWidgetFinder.Succeeded())
	//{
	//	wMultiPlayMenu = MyWidgetFinder.Class;
	//}
}

void UUIManager::Init()
{
	//FStringClassReference MyWidgetClassRef(TEXT("/Game/HUD/HUD_MyPlayerLayout.HUD_MyPlayerLayout"));
	//if (WidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>())
	//{
	//	//wUserWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);
	//	//wMultiPlayMenu = Cast<UHUD_PlayerLayout>(wUserWidget);
	//	int32 i = 10;
	//}
}
