// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMedic.h"
#include "MedicInteraction.h"
#include "Camera/CameraComponent.h"
#include "CombatMedic_PlayerController.h"
#include "MedicInventory.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	Stamina = StaminaMax;
	StopSprinting();
}

// Called every frame
void APlayerMedic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSprinting && GetCharacterMovement()->Velocity.Length() > 0)
	{
		Stamina = FMath::Clamp(Stamina - (StaminSprintUse * DeltaTime), 0, StaminaMax);
		if (Stamina <= 0)
		{
			StopSprinting();
		}
	}
	else if (!bSprinting && Stamina < StaminaMax)
	{
		Stamina = FMath::Clamp(Stamina + (StaminaRecharge * DeltaTime), 0, StaminaMax);
	}

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

void APlayerMedic::StartSprinting()
{
	bSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerMedic::StopSprinting()
{
	bSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

