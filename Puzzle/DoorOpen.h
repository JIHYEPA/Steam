// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "DoorOpen.generated.h"

UCLASS()
class NEOSTEAM_API ADoorOpen : public AActor
{
	GENERATED_BODY()

	class UTimelineComponent* OpenTimeline;
	
public:	

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* BaseDoor;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* LeftDoor;

	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveVector* vCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
		class APuzzleBase* PuzzleBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_IsAlreadySuccess, Category = "Puzzle")
		bool IsAlreadySuccess;

	FOnTimelineVector InterpFunction{};

	FOnTimelineEvent TimelineFinished{};

	class UNeoSteamGameInstance* NeoSteamGameInstance;

	FTimerHandle _loopTimerHandle;

	float CountdownTime = 1.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ADoorOpen();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void TimelineVectorReturn(FVector value);

	UFUNCTION()
		void OnTimelineFinished();

	UFUNCTION()
		void onTimerEnd();

	UFUNCTION(BlueprintCallable)
		void PuzzleOpen(int32 DoorIndex);

	/* RepNotify : IsAlreadySuccess*/

	UFUNCTION()
		void OnRep_IsAlreadySuccess();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_OnRep_IsAlreadySuccess();
	void Server_OnRep_IsAlreadySuccess_Implementation();
	bool Server_OnRep_IsAlreadySuccess_Validate();

	/*////////////////////////////*/

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
