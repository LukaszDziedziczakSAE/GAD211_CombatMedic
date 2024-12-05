// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatMedicGameMode.h"
#include "Soldier.h"
#include "SoldierWaypoint.h"
#include "SoldierCombat.h"
#include "Kismet/GameplayStatics.h"
#include "SoldierAIController.h"
#include "EnemySpawner.h"
#include "CombatMedic_HUD.h"
#include "Kismet/KismetMathLibrary.h"
#include "SoldierVoiceComponent.h"

ACombatMedicGameMode::ACombatMedicGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACombatMedicGameMode::BeginPlay()
{
	Super::BeginPlay();

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
			AliedSoldiers.Add(Soldier);
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

void ACombatMedicGameMode::SetNewCombatVoiceCountdown()
{
	CombatVoiceCountdown = UKismetMathLibrary::RandomFloatInRange(CombatVoiceMinTime, CombatVoiceMaxTime);
}

ASoldier* ACombatMedicGameMode::RandomSoldierInSquad()
{
	ASoldier* Soldier = nullptr;
	while (Soldier == nullptr)
	{
		int RanSoldierIndex = UKismetMathLibrary::RandomInteger64InRange(0, AliedSoldiers.Num() - 1);
		if (AliedSoldiers[RanSoldierIndex]->IsAlive() && !AliedSoldiers[RanSoldierIndex]->IsDowned())
		{
			Soldier = AliedSoldiers[RanSoldierIndex];
		}
	}

	return Soldier;
}

void ACombatMedicGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//UE_LOG(LogTemp, Warning, TEXT("GameMode tick"));
	if (CombatIndex != 0)
	{
		if (CombatVoiceCountdown > 0) CombatVoiceCountdown -= DeltaSeconds;

		if (CombatVoiceCountdown <= 0)
		{
			if (!AllEnemySoldiersDown())
			{
				RandomSoldierInSquad()->Voice->PlayCombatInProgress();
			}
			
			SetNewCombatVoiceCountdown();
		}
	}
}

void ACombatMedicGameMode::BeginCombat(int Index)
{
	if (CombatIndex == Index) return;
	CombatIndex = Index;
	UE_LOG(LogTemp, Warning, TEXT("Beginning Fight %d"), CombatIndex);

	TArray<ASoldierWaypoint*> AliedCombatPositions;
	for (ASoldierWaypoint* SoldierWaypoint : CombatPositions)
	{
		if (SoldierWaypoint->GetIndex() == CombatIndex && SoldierWaypoint->GetSide() == Allied)
		{
			AliedCombatPositions.Add(SoldierWaypoint);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Found %d AliedCombatPositions"), AliedCombatPositions.Num());

	for (ASoldier* AliedSoldier : AliedSoldiers)
	{
		if (!AliedSoldier->IsAlive()) continue;

		if (AliedCombatPositions.Num() > 0)
		{
			int RandomPositionIndex = UKismetMathLibrary::RandomInteger64InRange(0, AliedCombatPositions.Num() - 1);
			AliedSoldier->EngageCombat(AliedCombatPositions[RandomPositionIndex]);
			AliedCombatPositions.RemoveAt(RandomPositionIndex);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Ran out of AliedCombatPositions for %s"), *AliedSoldier->GetActorNameOrLabel());
		}
	}


	for (AEnemySpawner* Spawner : EnemySpawners)
	{
		if (Spawner->GetFightIndex() == CombatIndex)
		{
			ASoldier* Enemy = Spawner->SpawnEnemy();
			if (Enemy != nullptr) EnemySoldiers.Add(Enemy);
		}
	}

	RandomSoldierInSquad()->Voice->PlayCombatStart();
	SetNewCombatVoiceCountdown();
}

void ACombatMedicGameMode::TryEndCombat()
{
	UE_LOG(LogTemp, Warning, TEXT("TryEndCombat %d"), CombatIndex);
	if (CombatIndex == 0 || bAllAlliesDown) return;

	if (AllEnemySoldiersDown() && AllAlliesStanding())
	{
		for (ASoldier* Soldier : AliedSoldiers)
		{
			Soldier->DisengageCombat();
		}

		for (ASoldier* Enemy : EnemySoldiers)
		{
			if (Enemy->IsAlive()) Enemy->Death();
		}

		UE_LOG(LogTemp, Warning, TEXT("Ending Fight %d"), CombatIndex);
		CombatIndex = 0;

		RandomSoldierInSquad()->Voice->PlayCombatEnd();
	}
}

bool ACombatMedicGameMode::AllEnemySoldiersDown()
{
	for (ASoldier* Combatant : EnemySoldiers)
	{
		if (!Combatant->IsDowned())
		{
			UE_LOG(LogTemp, Display, TEXT("AllEnemySoldiersDown false"));
			return false;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("AllEnemySoldiersDown true"));
	return true;
}

bool ACombatMedicGameMode::AllAlliesStanding()
{
	for (ASoldier* Soldier : AliedSoldiers)
	{
		if (Soldier->IsAlive() && Soldier->IsDowned())
		{
			UE_LOG(LogTemp, Display, TEXT("AllAlliesStanding false"));
			return false;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("AllAlliesStanding true"));
	return true;
}

bool ACombatMedicGameMode::AllAlliesDown()
{
	for (ASoldier* Soldier : AliedSoldiers)
	{
		if (!Soldier->IsDowned() || Soldier->IsAlive())
		{
			UE_LOG(LogTemp, Display, TEXT("AllAlliesDown false"));
			return false;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("AllAlliesDown true"));
	return true;
}

bool ACombatMedicGameMode::AllAlliesDead()
{
	for (ASoldier* Soldier : AliedSoldiers)
	{
		if (Soldier->IsAlive())
		{
			UE_LOG(LogTemp, Display, TEXT("AllAlliesDead false"));
			return false;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("AllAlliesDead true"));
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

void ACombatMedicGameMode::EndIfAlliedSoldiersDead()
{
	if (!AllAlliesDead()) return;
	bAllAlliesDown = true;
	Cast<ACombatMedic_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowEndScreen();
}
