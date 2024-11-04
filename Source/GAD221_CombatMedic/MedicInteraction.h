// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MedicInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD221_COMBATMEDIC_API UMedicInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMedicInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bGivingMedicalAid;

	UPROPERTY()
	class ACombatMedic_HUD* HUD;

	UPROPERTY()
	class APlayerMedic* Player;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASoldier* Patient;

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintPure)
	bool GivingMedicalAid() { return bGivingMedicalAid; }
};
