// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMedicalItemType.h"
#include "FInventoryItem.generated.h"

USTRUCT(BlueprintType)
struct GAD221_COMBATMEDIC_API FInventoryItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EMedicalItemType> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;
};
