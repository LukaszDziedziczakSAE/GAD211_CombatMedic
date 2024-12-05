// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EMedicalItemType
{
	NoType UMETA(DisplayName = "No Type"),
	Bandage UMETA(DisplayName = "Bandage"),
	Tourniquet UMETA(DisplayName = "Tourniquet"),
	Gauze UMETA(DisplayName = "Gauze"),
	ChestSeal UMETA(DisplayName = "Chest Seal"),
	Scissors UMETA(DisplayName = "Scissors"),
	PainKiller UMETA(DisplayName = "Pain Killer")
};
