// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/TextRenderComponent.h"
#include "Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "Interaction/InterfaceActor.h"
#include "InteractionActor_NPC_Sparrow.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API AInteractionActor_NPC_Sparrow : public AInterfaceActor
{
	GENERATED_BODY()
	
public:
	AInteractionActor_NPC_Sparrow();

public:
	virtual bool BeginOutlineFocus_Implementation() override;
	virtual bool EndOutlineFocus_Implementation() override;	
	virtual bool Interact_Implementation(APlayerController* playercontroller) override;

	UFUNCTION(BlueprintImplementableEvent)
		void OpenUI(APlayerController* playercontroller);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBillboardComponent* Billboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextRender;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* InteractionCam;
};
