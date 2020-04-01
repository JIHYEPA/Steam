// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interaction/Interaction_Interface.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceActor.generated.h"

UCLASS()
class NEOSTEAM_API AInterfaceActor : public AActor, public IInteraction_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterfaceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	bool BeginOutlineFocus();
	virtual bool BeginOutlineFocus_Implementation() override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	bool EndOutlineFocus();
	virtual bool EndOutlineFocus_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	FString GetInteractionText();
	virtual FString GetInteractionText_Implementation() override;


	//반드시 재정의 해서 사용해야할 부분
	//실제로 상호작용하는 함수입니다.

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	bool Interact(APlayerController* playercontroller);
	virtual bool Interact_Implementation(APlayerController* playercontroller) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	bool BeginShowText();
	virtual bool BeginShowText_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	bool EndShowText();
	virtual bool EndShowText_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	bool GetIsUsed();
	virtual bool GetIsUsed_Implementation() override;

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString InteractionText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneCompoent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DefaultMesh;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	bool IsUsed;
};
