// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerMedic.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API APlayerMedic : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerMedic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMedicInteraction* MedicInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ACombatMedic_PlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMedicInventory* MedicInventory;

	UFUNCTION(BlueprintCallable)
	void Interact();
};

