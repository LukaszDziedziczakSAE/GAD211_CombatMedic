// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EMedicalItemType.h"
#include "MedicInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD221_COMBATMEDIC_API UMedicInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMedicInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Bandages{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Tourniquet{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Gauze{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ChestSeal{ 10 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PainKiller{ 10 };

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool HasEnoughItem(EMedicalItemType ItemType);

	UFUNCTION(BlueprintCallable)
	void UseItemType(EMedicalItemType ItemType);

	UFUNCTION(BlueprintCallable)
	void AddItemType(EMedicalItemType ItemType, int Amount = 1);

	UFUNCTION(BlueprintPure)
	int GetBandagesAmount() { return Bandages; }

	UFUNCTION(BlueprintPure)
	int GetTourniquetAmount() { return Tourniquet; }

	UFUNCTION(BlueprintPure)
	int GetGauzeAmount() { return Gauze; }

	UFUNCTION(BlueprintPure)
	int GetChestSealAmount() { return ChestSeal; }

	UFUNCTION(BlueprintPure)
	int GetPainKillerAmount() { return PainKiller; }
};
