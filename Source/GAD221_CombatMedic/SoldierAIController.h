// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoldierAIController.generated.h"


UCLASS()
class GAD221_COMBATMEDIC_API ASoldierAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASoldier* Soldier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASoldierWaypoint*> TravelWaypoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASoldierWaypoint*> CombatPositions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int LastTravelWaypointIndex;

public:
	UFUNCTION(BlueprintCallable)
	void SetWaypoint(FVector Location);

	UFUNCTION(BlueprintCallable)
	void SetFightingPosition(FVector Location);
	
	UFUNCTION(BlueprintCallable)
	void SetOpponent(ASoldier* Opponent);

	UFUNCTION(BlueprintCallable)
	void SetIsDowned(bool IsDowned);

	UFUNCTION(BlueprintCallable)
	void SetIsInCombat(bool InCombat);

	UFUNCTION(BlueprintCallable)
	void ArrivedAtWaypoint(int WaypointIndex);

	UFUNCTION(BlueprintCallable)
	void GoToLastWaypointSet();

	UFUNCTION(BlueprintCallable)
	void GoToNearestWaypoint();

	UFUNCTION(BlueprintCallable)
	void GoToGameModeLastWaypoint();
};
