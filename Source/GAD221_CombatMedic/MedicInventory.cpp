// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicInventory.h"

// Sets default values for this component's properties
UMedicInventory::UMedicInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMedicInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMedicInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UMedicInventory::HasEnoughItem(EMedicalItemType ItemType)
{
	switch (ItemType)
	{
	case EMedicalItemType::Bandage:
		return Bandages > 0;

	case EMedicalItemType::Tourniquet:
		return Tourniquet > 0;

	case EMedicalItemType::Gauze:
		return Gauze > 0;

	case EMedicalItemType::ChestSeal:
		return ChestSeal > 0;

	case EMedicalItemType::PainKiller:
		return PainKiller > 0;

	default:
		return true;
	}
}

void UMedicInventory::UseItemType(EMedicalItemType ItemType)
{
	switch (ItemType)
	{
	case EMedicalItemType::Bandage:
		Bandages--;
		break;

	case EMedicalItemType::Tourniquet:
		Tourniquet--;
		break;

	case EMedicalItemType::Gauze:
		Gauze--;
		break;

	case EMedicalItemType::ChestSeal:
		ChestSeal--;
		break;

	case EMedicalItemType::PainKiller:
		PainKiller--;
		break;
	}
}

void UMedicInventory::AddItemType(EMedicalItemType ItemType, int Amount)
{
	switch (ItemType)
	{
	case EMedicalItemType::Bandage:
		Bandages += Amount;
		break;

	case EMedicalItemType::Tourniquet:
		Tourniquet += Amount;
		break;

	case EMedicalItemType::Gauze:
		Gauze += Amount;
		break;

	case EMedicalItemType::ChestSeal:
		ChestSeal += Amount;
		break;

	case EMedicalItemType::PainKiller:
		PainKiller += Amount;
		break;
	}
}

