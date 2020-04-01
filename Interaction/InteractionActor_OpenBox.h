// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/InterfaceActor.h"
#include "Particles/ParticleSystem.h"
#include "InteractionActor_OpenBox.generated.h"

/**
 * 
 */
UCLASS()
class NEOSTEAM_API AInteractionActor_OpenBox : public AInterfaceActor
{
	GENERATED_BODY()

public:
	AInteractionActor_OpenBox();

	virtual bool Interact_Implementation(APlayerController* playercontroller) override;
	virtual bool BeginOutlineFocus_Implementation() override;

	UFUNCTION(BlueprintCallable)
		virtual bool EndOutlineFocus_Implementation() override;
	
	virtual FString GetInteractionText_Implementation() override;

public:
	UFUNCTION()
	void OpenBox();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Cover;

	UParticleSystem* Particle;
	
};
