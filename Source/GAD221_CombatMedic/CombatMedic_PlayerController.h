// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatMedic_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAD221_COMBATMEDIC_API ACombatMedic_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;

	UPROPERTY()
	class APlayerMedic* PlayerMedic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_LeftMouse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_CallEvac;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* IA_Sprint;

	UFUNCTION()
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Interact(const FInputActionValue& Value);

	UFUNCTION()
	void LeftMouseUp(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraTransitionTime;

	UFUNCTION()
	void CallEvac();

	UFUNCTION()
	void SprintStart();

	UFUNCTION()
	void SprintStop();
	
public:
	UFUNCTION()
	void SwitchToPatientCamera();

	UFUNCTION()
	void SwitchToBackToMainCamera();

	UFUNCTION(BlueprintCallable)
	UShapeComponent* ComponentUnderMouse();
};
