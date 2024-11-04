// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBodyPart.h"
#include "FInjury.generated.h"

USTRUCT(BlueprintType)
struct GAD221_COMBATMEDIC_API FInjury
{
	GENERATED_BODY()

public: 
	FInjury();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBodyPart> BodyPart;

	void GenerateNew();

	float GetPercentage() { return CurrentAmount / MaxAmount; }
};
