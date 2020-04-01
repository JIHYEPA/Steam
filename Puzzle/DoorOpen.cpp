// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "NeoSteam/GamePlayFramework/NeoSteamGameInstance.h"

// Sets default values
ADoorOpen::ADoorOpen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	IsAlreadySuccess = false;

	BaseDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseDoor"));
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));

	RootComponent = BaseDoor;
	LeftDoor->SetupAttachment(BaseDoor);
	RightDoor->SetupAttachment(BaseDoor);
	
	BaseDoor->SetVisibility(false);
	LeftDoor->SetCollisionProfileName("BlockAll");
	RightDoor->SetCollisionProfileName("BlockAll");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LeftDoorMesh(TEXT("/Game/Map/Props/ActorMerged/SM_MERGED_LeftDoor"));

	if (LeftDoorMesh.Succeeded())
	{
		LeftDoor->SetStaticMesh(LeftDoorMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RightDoorMesh(TEXT("/Game/Map/Props/ActorMerged/SM_MERGED_RightDoor"));

	if (RightDoorMesh.Succeeded())
	{
		RightDoor->SetStaticMesh(RightDoorMesh.Object);
	}

	LeftDoor->SetRelativeLocation(FVector(-630.0f, 0.0f, 0.0f));
	RightDoor->SetRelativeLocation(FVector(630.0f, 0.0f, 0.0f));

	/* TimeLine */

	OpenTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	InterpFunction.BindUFunction(this, FName("TimelineVectorReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
}

// Called when the game starts or when spawned
void ADoorOpen::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADoorOpen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoorOpen::TimelineVectorReturn(FVector value)
{
	LeftDoor->SetRelativeLocation(value);
	RightDoor->SetRelativeLocation(-value);
}

void ADoorOpen::OnTimelineFinished()
{
	//NeoSteamGameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());
	//CameraManager->SetCameraReturntoPlayer
}

void ADoorOpen::onTimerEnd()
{
	--CountdownTime;
	if (CountdownTime < 1) //TimeOut
	{
		GetWorldTimerManager().ClearTimer(_loopTimerHandle); //Timer Stop

		//Delay
		//OpenTimeline->Play();
	}
}

void ADoorOpen::PuzzleOpen(int32 DoorIndex)
{
	if (vCurve)
	{
		OpenTimeline->AddInterpVector(vCurve, InterpFunction, FName("Alpha"));
		OpenTimeline->SetTimelineFinishedFunc(TimelineFinished);

		OpenTimeline->SetTimelineLength(2.0f);

		//IsAlreadySuccess = true;
		Server_OnRep_IsAlreadySuccess();

		NeoSteamGameInstance = Cast<UNeoSteamGameInstance>(GetGameInstance());
		//CameraManager->SetDoorOpenCam

		switch (DoorIndex)
		{
		case 0:
			/*CountdownTime = 1.5f;
			GetWorldTimerManager().SetTimer(_loopTimerHandle, this, &ADoorOpen::onTimerEnd, CountdownTime, false);*/
			OpenTimeline->Play();
			break;
		case 1:
			/*CountdownTime = 3.0f;
			GetWorldTimerManager().SetTimer(_loopTimerHandle, this, &ADoorOpen::onTimerEnd, CountdownTime, false);*/
			OpenTimeline->Play();
			break;
		default:
			OpenTimeline->Play();
			break;
		}
	}
}

/* RepNotify : IsAlreadySuccess*/
void ADoorOpen::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ADoorOpen, IsAlreadySuccess, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME(ADoorOpen, IsAlreadySuccess);
}

bool ADoorOpen::Server_OnRep_IsAlreadySuccess_Validate()
{
	return true;
}

void ADoorOpen::Server_OnRep_IsAlreadySuccess_Implementation()
{
	if (Role == ROLE_Authority)
	{
		IsAlreadySuccess = true;
		if (GetNetMode() != NM_DedicatedServer)
		{
			OnRep_IsAlreadySuccess();
		}
	}
	/*else
	{
		if (IsAlreadySuccess == true)
		{
			OpenTimeline->Play();
		}
	}*/
}

void ADoorOpen::OnRep_IsAlreadySuccess()
{
	//OpenTimeline->Play();
}