// Fill out your copyright notice in the Description page of Project Settings.


#include "FInjury.h"
#include "Kismet/KismetMathLibrary.h"

FInjury::FInjury()
{
	MaxAmount = 0;
	CurrentAmount = 0;
	BodyPart = None;
}

void FInjury::GenerateNew()
{
	MaxAmount = UKismetMathLibrary::RandomFloatInRange(0.0f, 100.0f);
	CurrentAmount = MaxAmount;
	int RanBodyPartIndex = UKismetMathLibrary::RandomInteger64InRange(0, 10);
	BodyPart = static_cast<TEnumAsByte<EBodyPart>>(RanBodyPartIndex);
}
