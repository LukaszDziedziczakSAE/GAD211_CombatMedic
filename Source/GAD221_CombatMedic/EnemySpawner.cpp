// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Soldier.h"
#include "SoldierAIController.h"
#include "SoldierWaypoint.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (EnemyPrefab == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing EnemyPrefab"), *GetName());
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ASoldier* AEnemySpawner::SpawnEnemy()
{
	if (GoToWaypoint == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing GoToWaypoint reference"), *GetName());
		return nullptr;
	}

	ASoldier* NewSoldier = GetWorld()->SpawnActor<ASoldier>(EnemyPrefab, GetActorLocation(), GetActorRotation());
	if (NewSoldier == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s failed to spawn Soldier for %s"), *GetActorNameOrLabel(), *GoToWaypoint->GetActorNameOrLabel());
		return nullptr;
	}

	
	NewSoldier->EngageCombat(GoToWaypoint);
	return NewSoldier;
}

