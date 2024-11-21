// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatMedicGameMode.h"
#include "Soldier.h"
#include "SoldierWaypoint.h"
#include "SoldierCombat.h"
#include "Kismet/GameplayStatics.h"
#include "SoldierAIController.h"
#include "EnemySpawner.h"
#include "CombatMedic_HUD.h"

void ACombatMedicGameMode::BeginPlay()
{
	TArray<AActor*> WaypointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldierWaypoint::StaticClass(), WaypointActors);
	
	for (AActor* WaypointActor : WaypointActors)
	{
		ASoldierWaypoint* Waypoint = Cast<ASoldierWaypoint>(WaypointActor);
		if (Waypoint == nullptr) continue;

		if (Waypoint->GetWaypointType() == Travel)
		{
			TravelWaypoints.Add(Waypoint);
			if (Waypoint->GetIndex() == 0)
			{
				FirstTravelWaypoint = Waypoint;
			}
		}

		else if (Waypoint->GetWaypointType() == FightingPosition)
		{
			CombatPositions.Add(Waypoint);
		}
	}

	TArray<AActor*> SoldierActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldier::StaticClass(), SoldierActors);

	for (AActor* SoldierActor : SoldierActors)
	{
		ASoldier* Soldier = Cast<ASoldier>(SoldierActor);
		if (Soldier == nullptr) continue;

		if (Soldier->SoldierSide == Allied && FirstTravelWaypoint != nullptr)
		{
			AllySoldiers.Add(Soldier);
			//Soldier->SoldierAI()->SetWaypoint(FirstTravelWaypoint->GetActorLocation());
		}
	}

	TArray<AActor*> SpawnerActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), SpawnerActors);

	for (AActor* SpawnerActor : SpawnerActors)
	{
		AEnemySpawner* Spawner = Cast<AEnemySpawner>(SpawnerActor);
		if (Spawner == nullptr) continue;

		EnemySpawners.Add(Spawner);
	}
}

void ACombatMedicGameMode::BeginCombat(int Index)
{
	if (CombatIndex == Index) return;
	UE_LOG(LogTemp, Warning, TEXT("Begining Fight %d"), CombatIndex);
	CombatIndex = Index;

	TArray<ASoldierWaypoint*> AllyCombatPositions;
	for (ASoldierWaypoint* SoldierWaypoint : CombatPositions)
	{
		if (SoldierWaypoint->GetIndex() == CombatIndex && SoldierWaypoint->GetSide() == Allied)
		{
			AllyCombatPositions.Add(SoldierWaypoint);
		}
	}

	for (ASoldier* AllySoldier : AllySoldiers)
	{
		if (AllyCombatPositions.Num() > 0)
		{
			AllySoldier->EngageCombat(AllyCombatPositions[0]);
			AllyCombatPositions.RemoveAt(0);
		}
	}


	for (AEnemySpawner* Spawner : EnemySpawners)
	{
		if (Spawner->GetFightIndex() == CombatIndex)
		{
			EnemySoldiers.Add(Spawner->SpawnEnemy());
		}
	}
}

void ACombatMedicGameMode::TryEndCombat()
{
	if (AllEnemySoldiersDown() && AllAlliesStanding())
	{
		for (ASoldier* Soldier : AllySoldiers)
		{
			Soldier->DisengageCombat();
		}

		for (ASoldier* Enemy : EnemySoldiers)
		{
			Enemy->Death();
		}

		UE_LOG(LogTemp, Warning, TEXT("Begining Fight %d"), CombatIndex);
		CombatIndex = 0;
	}
}

bool ACombatMedicGameMode::AllEnemySoldiersDown()
{
	for (ASoldier* Combatant : EnemySoldiers)
	{
		if (!Combatant->IsDowned())
		{
			return false;
		}
	}
	return true;
}

bool ACombatMedicGameMode::AllAlliesStanding()
{
	for (ASoldier* Soldier : AllySoldiers)
	{
		if (Soldier->IsDowned())
		{
			return false;
		}
	}
	return true;
}

bool ACombatMedicGameMode::AllAlliesDown()
{
	for (ASoldier* Soldier : AllySoldiers)
	{
		if (!Soldier->IsDowned())
		{
			return false;
		}
	}
	return true;
}

void ACombatMedicGameMode::PlayerEnteredDangerZone()
{
	bPlayerDied = true;
	Cast<ACombatMedic_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowEndScreen();
}

void ACombatMedicGameMode::SoldiersGotToLevelEnd()
{
	bLevelEnded = true;
	Cast<ACombatMedic_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowEndScreen();
}

void ACombatMedicGameMode::EndIfAllySoldiersAllDown()
{
	if (!AllAlliesDown()) return;
	bAllAlliesDown = true;
	Cast<ACombatMedic_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowEndScreen();
}
