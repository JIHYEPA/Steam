// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_PlayerLayout.h"

void UHUD_PlayerLayout::Init()
{
	InterfaceText->SetVisibility(ESlateVisibility::Hidden);
}

void UHUD_PlayerLayout::ShowInteractionText(FString InterText)
{
	FString text = FString("[E] ");
	text.Append(InterText);

	InterfaceText->SetText(FText::FromString(text));
	InterfaceText->SetVisibility(ESlateVisibility::Visible);
}

void UHUD_PlayerLayout::EndInteractionText()
{
	InterfaceText->SetVisibility(ESlateVisibility::Hidden);
}
