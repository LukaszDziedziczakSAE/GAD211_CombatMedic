// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMedic.h"
#include "MedicInteraction.h"
#include "Camera/CameraComponent.h"
#include "CombatMedic_PlayerController.h"
#include "MedicInventory.h"

// Sets default values
APlayerMedic::APlayerMedic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MedicInteraction = CreateDefaultSubobject<UMedicInteraction>(TEXT("Medic Interaction"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(GetRootComponent());

	MedicInventory = CreateDefaultSubobject<UMedicInventory>(TEXT("Medic Inventory"));
}

// Called when the game starts or when spawned
void APlayerMedic::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<ACombatMedic_PlayerController>(GetController());
}

// Called every frame
void APlayerMedic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerMedic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerMedic::Interact()
{
	if (MedicInteraction->Patient != nullptr)
	{
		MedicInteraction->Interact();
	}

	else if (MedicInteraction->HasItemToPickup())
	{
		MedicInteraction->PickUpItem();
	}
}

bool APlayerMedic::IsProvidingMedicalAid()
{
	if (MedicInteraction == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerMedic missing MedicInteraction"));
		return false;
	}

	return MedicInteraction->GivingMedicalAid();
}

bool APlayerMedic::HasPatient()
{
	return MedicInteraction->Patient != nullptr;
}

