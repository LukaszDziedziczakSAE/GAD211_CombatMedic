// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EMedicalItemType.h"
#include "FMedicalAffect.h"
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

	UPROPERTY(VisibleAnywhere)
	bool bGivingMedicalAid;

	UPROPERTY()
	class ACombatMedic_HUD* HUD;

	UPROPERTY()
	class APlayerMedic* Player;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EMedicalItemType> InteractionType;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASoldier* Patient;

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintPure)
	bool GivingMedicalAid();

	UFUNCTION(BlueprintCallable)
	void StartMedicalItemApplication(TEnumAsByte<EMedicalItemType> ItemType);

	UFUNCTION(BlueprintCallable)
	void EndMedicalItemApplication(class UShapeComponent* HitShape);

	UFUNCTION(BlueprintPure)
	TEnumAsByte<EMedicalItemType> GetInteractionType() { return InteractionType; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMedicalAffect> MedicalAffects;

	UFUNCTION(BlueprintCallable)
	float AmountByAffect(TEnumAsByte<EMedicalItemType> ItemType, TEnumAsByte<EBodyPart> BodyPart);
};
