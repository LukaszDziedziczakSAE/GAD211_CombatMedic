// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBodyPart.h"
#include "EMedicalItemType.h"
#include "FMedicalAffect.generated.h"

USTRUCT(BlueprintType)
struct GAD221_COMBATMEDIC_API FMedicalAffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EMedicalItemType> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBodyPart> BodyPart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount;
};
