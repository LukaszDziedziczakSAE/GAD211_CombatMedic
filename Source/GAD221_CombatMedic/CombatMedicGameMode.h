// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatMedicGameMode.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API ACombatMedicGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASoldier*> AllySoldiers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASoldier*> EnemySoldiers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASoldierWaypoint*> TravelWaypoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASoldierWaypoint*> CombatPositions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class AEnemySpawner*> EnemySpawners;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASoldierWaypoint* FirstTravelWaypoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CombatIndex;

public:
	UFUNCTION(BlueprintCallable)
	ASoldierWaypoint* GetFirstTravelWaypoint() { return FirstTravelWaypoint; }

	UFUNCTION(BlueprintCallable)
	void BeginCombat(int CombaIndex);

	UFUNCTION(BlueprintCallable)
	void TryEndCombat();

	UFUNCTION(BlueprintCallable)
	bool AllEnemySoldiersDown();

	UFUNCTION(BlueprintCallable)
	bool AllAlliesStanding();
};
