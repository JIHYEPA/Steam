// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMontage.h"
#include "Engine/Engine.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "NeoSteamCharacter.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
ULevelMontage::ULevelMontage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevelMontage::BeginPlay()
{
	Super::BeginPlay();

	bPlayMontage = false;
	// ...
	MontageEnded.BindUObject(this, &ULevelMontage::EndAnimMontage);
	
}
 
// Called every frame
void ULevelMontage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULevelMontage::PlayAnimMontage(FNSCharacterMontageData MontageData)
{
	if (bPlayMontage)
	{
		if (PlayingPriority <= MontageData.Priority)
		{
			return false;
		}
		else
		{
			StopAnimMontage();
		}
	}
	
	ANeoSteamCharacter* Character = Cast<ANeoSteamCharacter>(GetOwner());
	UAnimMontage* Montage = Cast<UAnimMontage>(MontageData.MontageRef.TryLoad());
	
	if (Montage != nullptr)
	{
		bPlayMontage = true;
		PlayingPriority = MontageData.Priority;
		Character->PlayAnimMontage(Montage);
	}
	else
	{
		return false;
	}
	//Montage->get
	Character->GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEnded, Montage);
	
	return true;
}

void ULevelMontage::EndAnimMontage(UAnimMontage* AnimMontage, bool bInterrupted)
{
	bPlayMontage = false;
}

void ULevelMontage::StopAnimMontage()
{
	ANeoSteamCharacter* Character = Cast<ANeoSteamCharacter>(GetOwner());
	
	if (Character && Character->GetMesh())
	{
		Character->GetMesh()->GetAnimInstance()->Montage_Stop(0.25f);

		bPlayMontage = false;
		PlayingPriority = 0;
		//AnimMontage Related State Init

		//Camera Shake & Camera Move reset	

	}
}



//for (FSoftObjectPath AssetRef : Settings->AdditionalParameterTypes)
//{
//	TotalStructAssets.AddUnique(AssetRef);
//}
