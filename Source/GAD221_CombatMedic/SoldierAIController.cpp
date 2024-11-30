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
			}

			else if (Waypoint->GetWaypointType() == FightingPosition)
			{
				CombatPositions.Add(Waypoint);
			}
		}

		ASoldierWaypoint* NearestWaypoint = nullptr;
		float NearestWaypointDistance = 100000;
		for (ASoldierWaypoint* Waypoint : TravelWaypoints)
		{
			float Distance = FVector::Distance(Soldier->GetActorLocation(), Waypoint->GetActorLocation());

			if (NearestWaypoint == nullptr)
			{
				NearestWaypoint = Waypoint;
				NearestWaypointDistance = Distance;
			}

			else if (Distance < NearestWaypointDistance)
			{
				NearestWaypoint = Waypoint;
				NearestWaypointDistance = Distance;
			}
		}

		if (NearestWaypoint != nullptr)
		{
			LastTravelWaypointIndex = NearestWaypoint->GetIndex();
			SetWaypoint(NearestWaypoint->RandomPointInRadius());
		}
		else UE_LOG(LogTemp, Error, TEXT("Did not find Nearest Waypoint"));
	}
}

void ASoldierAIController::SetWaypoint(FVector Location)
{
	GetBlackboardComponent()->SetValueAsVector(TEXT("Waypoint"), Location);
}

void ASoldierAIController::SetFightingPosition(FVector Location)
{
	GetBlackboardComponent()->SetValueAsVector(TEXT("FightingPosition"), Location);
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
			SetWaypoint(Waypoint->RandomPointInRadius());
		}
	}
}
