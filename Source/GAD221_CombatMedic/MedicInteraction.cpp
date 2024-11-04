// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicInteraction.h"
#include "CombatMedic_HUD.h"
#include "PlayerMedic.h"
#include "CombatMedic_PlayerController.h"
#include "Soldier.h"
#include "Components/ShapeComponent.h"

// Sets default values for this component's properties
UMedicInteraction::UMedicInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMedicInteraction::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ACombatMedic_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	Player = Cast<APlayerMedic>(GetOwner());
}


// Called every frame
void UMedicInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMedicInteraction::Interact()
{
	if (HUD == nullptr || Patient == nullptr) return;

	if (!bGivingMedicalAid)
	{
		bGivingMedicalAid = true;
		HUD->ShowMedicInterface();
		Player->PlayerController->SwitchToPatientCamera();
	}

	else
	{
		bGivingMedicalAid = false;
		HUD->ShowCombatHUD();
		Player->PlayerController->SwitchToBackToMainCamera();
	}
}

bool UMedicInteraction::GivingMedicalAid()
{
	return bGivingMedicalAid && InteractionType != None;
}

void UMedicInteraction::StartMedicalItemApplication(TEnumAsByte<EMedicalItemType> ItemType)
{
	InteractionType = ItemType;
}

void UMedicInteraction::EndMedicalItemApplication(UShapeComponent* HitShape)
{
	if (HitShape != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Apply to %s"), *HitShape->GetName());

		TEnumAsByte<EBodyPart> BodyPart = Patient->BodyPartFromShape(HitShape);

		if (BodyPart == Patient->GetInjury().BodyPart)
		{
			Patient->HealInjury(AmountByAffect(InteractionType, BodyPart));
		}

	}
	
	else UE_LOG(LogTemp, Warning, TEXT("EndMedicalItemApplication"));




	InteractionType = NoType;
}

float UMedicInteraction::AmountByAffect(TEnumAsByte<EMedicalItemType> ItemType, TEnumAsByte<EBodyPart> BodyPart)
{
	for (FMedicalAffect Affect : MedicalAffects)
	{
		if (Affect.ItemType == ItemType && Affect.BodyPart == BodyPart)
		{
			return Affect.Amount;
		}
	}

	return 0.0f;
}

