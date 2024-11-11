// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Soldier.h"
#include "SoldierCombat.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CombatMedicGameMode.h"
#include "SoldierWaypoint.h"
#include "Kismet/GameplayStatics.h"

void ASoldierAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Soldier = Cast<ASoldier>(InPawn);

	if (Soldier == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Soldier reference"));
		return;
	}

	RunBehaviorTree(BehaviorTree);

	if (Soldier->SoldierSide == Allied)
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
					SetWaypoint(Waypoint->GetActorLocation());
				}
			}

			else if (Waypoint->GetWaypointType() == FightingPosition)
			{
				CombatPositions.Add(Waypoint);
			}
		}
	}

	/*else if (Soldier->SoldierSide == Enemy)
	{
		SetIsInCombat(true);

		if (Soldier->Combat->GetFightingPosition() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AI cannot find fighting position"));
			return;
		}

		SetWaypoint(Soldier->Combat->GetFightingPosition()->GetActorLocation());
	}*/
}

void ASoldierAIController::SetWaypoint(FVector Location)
{
	GetBlackboardComponent()->SetValueAsVector(TEXT("Waypoint"), Location);
}

void ASoldierAIController::SetOpponent(ASoldier* Opponent)
{
	GetBlackboardComponent()->SetValueAsObject(TEXT("Opponent"), Opponent);
}

void ASoldierAIController::SetIsDowned(bool IsDowned)
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("Downed"), IsDowned);
}

void ASoldierAIController::SetIsInCombat(bool InCombat)
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("InCombat"), InCombat);
}

void ASoldierAIController::ArrivedAtWaypoint(int WaypointIndex)
{
	LastTravelWaypointIndex = WaypointIndex + 1;
	GoToLastWaypointSet();
}

void ASoldierAIController::GoToLastWaypointSet()
{
	if (TravelWaypoints.Num() == 0) return;

	for (ASoldierWaypoint* Waypoint : TravelWaypoints)
	{
		if (Waypoint->GetIndex() == LastTravelWaypointIndex)
		{
			SetWaypoint(Waypoint->GetActorLocation());
		}
	}
}
