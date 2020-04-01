// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataType/NSEnum.h"
#include "SpawnActor.generated.h"

UCLASS()
class NEOSTEAM_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

	UFUNCTION(BlueprintCallable)
		AActor* SpawnCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Spawn")
		int32 SpawnAmount;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Spawn")
		ENSCharacterID CharacterID;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* Bound;
};
