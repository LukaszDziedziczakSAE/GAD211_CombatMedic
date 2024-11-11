// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ASoldier> EnemyPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ASoldierWaypoint* GoToWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int FightIndex;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int GetFightIndex() { return FightIndex; }

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
};
