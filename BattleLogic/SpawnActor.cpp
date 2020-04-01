// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include "Components/BoxComponent.h"
#include "EnumStruct.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "NeoSteamCharacter.h"
#include "Character/NeoSteamMonster.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bound = CreateDefaultSubobject<UBoxComponent>("BoundCollision");
	Bound->SetupAttachment(RootComponent);
	Bound->SetHiddenInGame(true);
}

AActor* ASpawnActor::SpawnCharacter()
{
	FCollisionQueryParams Params(NAME_None, false, this);
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectType;
	FHitResult OnHit;
	FVector StartVec;
	FVector RandPoint = UKismetMathLibrary::RandomPointInBoundingBox(Bound->Bounds.Origin, Bound->Bounds.BoxExtent);
	StartVec.X = RandPoint.X;
	StartVec.Y = RandPoint.Y;
	StartVec.Z = RandPoint.Z + 10000;
	FVector EndVec = StartVec + (GetActorUpVector() * -15000);

	// draw collision line
	DrawDebugLine(GetWorld(), StartVec, EndVec, FColor::Red, false, 3.0f);

	//LineTrace
	bool IsHit = GetWorld()->LineTraceSingleByObjectType(
		OnHit,
		StartVec,
		EndVec,
		TraceObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic)),
		Params
	);

	if (IsHit)
	{
		FVector TLocation = UKismetMathLibrary::MakeVector(OnHit.ImpactPoint.X, OnHit.ImpactPoint.Y, OnHit.ImpactPoint.Z + 100.0f);
		FRotator TRotator = UKismetMathLibrary::MakeRotator(0.0f, 0.0f, UKismetMathLibrary::RandomFloat());
		FTransform SpawnTransform = UKismetMathLibrary::MakeTransform(TLocation, TRotator, UKismetMathLibrary::MakeVector(1.0f, 1.0f, 1.0f));

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		//Spawn Actor
		AActor* SpawnActorRef = GetWorld()->SpawnActor<AActor>(ANeoSteamMonster::StaticClass(), SpawnTransform, ActorSpawnParams);

		ANeoSteamCharacter* SpawnChara = Cast<ANeoSteamMonster>(SpawnActorRef);
		SpawnChara->Init(CharacterID);

		return SpawnChara;
	}
	return nullptr;
}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
