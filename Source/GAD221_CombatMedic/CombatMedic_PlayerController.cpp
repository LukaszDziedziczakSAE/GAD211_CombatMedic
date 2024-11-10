// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatMedic_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerMedic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Soldier.h"
#include "MedicInteraction.h"
#include "Components/ShapeComponent.h"

void ACombatMedic_PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatMedic_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerMedic = Cast<APlayerMedic>(aPawn);
}

void ACombatMedic_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem != nullptr && InputMapping != nullptr)
	{
		InputSubsystem->ClearAllMappings();
		InputSubsystem->AddMappingContext(InputMapping, 0);
	}
	else if (InputSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Subsystem Referance"), *GetName());
		return;
	}
	else if (InputMapping == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Mapping Referance"), *GetName());
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (Input != nullptr)
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ACombatMedic_PlayerController::Move);
		Input->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ACombatMedic_PlayerController::Look);
		Input->BindAction(IA_Interact, ETriggerEvent::Started, this, &ACombatMedic_PlayerController::Interact);
		Input->BindAction(IA_LeftMouse, ETriggerEvent::Completed, this, &ACombatMedic_PlayerController::LeftMouseUp);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Input Referance"));
	}
}

void ACombatMedic_PlayerController::Move(const FInputActionValue& Value)
{
	if (PlayerMedic == nullptr || PlayerMedic->IsProvidingMedicalAid()) return;

	FRotator CharacterRotation = PlayerMedic->GetControlRotation();

	PlayerMedic->AddMovementInput(
		UKismetMathLibrary::GetForwardVector(FRotator{ 0.0f, CharacterRotation.Yaw, 0.0f }),
		Value.Get<FVector2D>().Y);

	PlayerMedic->AddMovementInput(
		UKismetMathLibrary::GetRightVector(FRotator{ 0.0f, CharacterRotation.Yaw, CharacterRotation.Roll }),
		Value.Get<FVector2D>().X);
}

void ACombatMedic_PlayerController::Look(const FInputActionValue& Value)
{
	//if (PlayerMedic == nullptr) return;

	AddYawInput(Value.Get<FVector2D>().X);
	AddPitchInput(-1 * Value.Get<FVector2D>().Y);
}

void ACombatMedic_PlayerController::Interact(const FInputActionValue& Value)
{
	if (PlayerMedic == nullptr) return;

	PlayerMedic->Interact();
}

void ACombatMedic_PlayerController::LeftMouseUp(const FInputActionValue& Value)
{
	if (PlayerMedic == nullptr) return;
	if (PlayerMedic->MedicInteraction->GivingMedicalAid()) PlayerMedic->MedicInteraction->EndMedicalItemApplication(ComponentUnderMouse());
}

void ACombatMedic_PlayerController::SwitchToPatientCamera()
{
	AActor* Patient = Cast<AActor>(PlayerMedic->MedicInteraction->Patient);
	SetViewTargetWithBlend(Patient, CameraTransitionTime, EViewTargetBlendFunction::VTBlend_Linear);
	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}

void ACombatMedic_PlayerController::SwitchToBackToMainCamera()
{
	SetViewTargetWithBlend(PlayerMedic, CameraTransitionTime, EViewTargetBlendFunction::VTBlend_Linear);
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}

UShapeComponent* ACombatMedic_PlayerController::ComponentUnderMouse()
{
	FHitResult Hit;
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
	FVector TraceStart = MouseWorldLocation;
	FVector TraceEnd = MouseWorldLocation + MouseWorldDirection * 1000.0f;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(PlayerMedic);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_GameTraceChannel1, QueryParams);

	if (Hit.bBlockingHit)
	{
		UShapeComponent* ShapeComponent = Cast<UShapeComponent>(Hit.Component);

		if (ShapeComponent != nullptr) return ShapeComponent;
	}

	return nullptr;
}
