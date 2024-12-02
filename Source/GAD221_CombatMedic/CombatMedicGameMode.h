// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatMedicGameMode.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API ACombatMedicGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACombatMedicGameMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ASoldier*> AliedSoldiers;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bPlayerDied;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bLevelEnded;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bAllAlliesDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CombatVoiceCountdown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CombatVoiceMinTime{5.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CombatVoiceMaxTime{10.0f};

	UFUNCTION()
	void SetNewCombatVoiceCountdown();

	UFUNCTION()
	class ASoldier* RandomSoldierInSquad();

public:
	virtual void Tick(float DeltaSeconds) override;

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

	UFUNCTION(BlueprintCallable)
	bool AllAlliesDown();

	UFUNCTION(BlueprintCallable)
	bool AllAlliesDead();

	UFUNCTION(BlueprintCallable)
	void PlayerEnteredDangerZone();

	UFUNCTION(BlueprintCallable)
	void SoldiersGotToLevelEnd();

	UFUNCTION(BlueprintCallable)
	void EndIfAlliedSoldiersDead();

	UFUNCTION(BlueprintPure)
	int GetCombatIndex() { return CombatIndex; }
};
