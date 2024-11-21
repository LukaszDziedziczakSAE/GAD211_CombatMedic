// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombatMedic_HUD.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API ACombatMedic_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowMedicInterface();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowCombatHUD();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowEndScreen();
};
