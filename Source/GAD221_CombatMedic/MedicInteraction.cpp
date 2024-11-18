// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicInteraction.h"
#include "CombatMedic_HUD.h"
#include "PlayerMedic.h"
#include "CombatMedic_PlayerController.h"
#include "Soldier.h"
#include "Components/ShapeComponent.h"
#include "MedicInventory.h"
#include "ItemPickup.h"

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

	ApplicationCurrent = MedApplicationTime;
}


// Called every frame
void UMedicInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ApplicationCurrent < MedApplicationTime)
	{
		ApplicationCurrent += DeltaTime;

		if (ApplicationCurrent >= MedApplicationTime)
		{
			ApplicationCurrent = MedApplicationTime;
			CompleteMedicalItemApplication();
		}
	}
}

void UMedicInteraction::Interact()
{
	if (HUD == nullptr || Patient == nullptr) return;

	if (!bGivingMedicalAid && Patient->IsDowned())
	{
		bGivingMedicalAid = true;
		HUD->ShowMedicInterface();
		Player->PlayerController->SwitchToPatientCamera();
	}

	else if (bGivingMedicalAid)
	{
		bGivingMedicalAid = false;
		HUD->ShowCombatHUD();
		Player->PlayerController->SwitchToBackToMainCamera();
	}
}

bool UMedicInteraction::GivingMedicalAid()
{
	return bGivingMedicalAid;
}

void UMedicInteraction::StartMedicalItemApplication(TEnumAsByte<EMedicalItemType> ItemType)
{
	if (BodyPartSelected != None) return;
	if (!Player->MedicInventory->HasEnoughItem(ItemType)) return;


	InteractionType = ItemType;
}

void UMedicInteraction::EndMedicalItemApplication(UShapeComponent* HitShape)
{
	if (BodyPartSelected != None || InteractionType == NoType) return;

	if (HitShape != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Apply to %s"), *HitShape->GetName());

		TEnumAsByte<EBodyPart> BodyPart = Patient->BodyPartFromShape(HitShape);

		if (BodyPart == Patient->GetInjury().BodyPart)
		{
			BodyPartSelected = BodyPart;
			ApplicationCurrent = 0;
		}
	}
	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EndMedicalItemApplication"));

		InteractionType = NoType;
	}
}

void UMedicInteraction::CompleteMedicalItemApplication()
{
	if (BodyPartSelected == None) return;

	Patient->HealInjury(AmountByAffect(InteractionType, BodyPartSelected));

	if (!Patient->IsDowned())
	{
		Interact();
		Patient = nullptr;
	}

	Player->MedicInventory->UseItemType(InteractionType);

	BodyPartSelected = None;
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

void UMedicInteraction::PickUpItem()
{
	if (ItemPickup == nullptr) return;

	if (ItemPickup->GetInventoryItems().Num() > 0)
	{
		for (FInventoryItem InventoryItem : ItemPickup->GetInventoryItems())
		{
			Player->MedicInventory->AddItemType(InventoryItem.ItemType, InventoryItem.Amount);
		}

		ItemsPickedUp.Broadcast(ItemPickup->GetInventoryItems());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no medical items"), *ItemPickup->GetName());
	}

	ItemPickup->Destroy();
	ItemPickup = nullptr;
}

