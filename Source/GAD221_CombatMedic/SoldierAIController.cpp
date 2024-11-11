// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Soldier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CombatMedicGameMode.h"
#include "SoldierWaypoint.h"
#include "Kismet/GameplayStatics.h"

void ASoldierAIController::OnPossess(APawn* InPawn)
{
	Soldier = Cast<ASoldier>(InPawn);

	RunBehaviorTree(BehaviorTree);

	TArray<AActor*> WaypointActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldierWaypoint::StaticClass(), WaypointActors);

	for (AActor* WaypointActor : WaypointActors)
	{
		ASoldierWaypoint* Waypoint = Cast<ASoldierWaypoint>(WaypointActor);
		if (Waypoint == nullptr) continue;

		if (Waypoint->GetWaypointType() == Travel)
		{
			TravelWaypoints.Add(Waypoint);
			/*if (Waypoint->GetIndex() == 0)
			{
				SetWaypoint(Waypoint->GetActorLocation());
			}*/
		}

		else if (Waypoint->GetWaypointType() == FightingPosition)
		{
			CombatPositions.Add(Waypoint);
		}
	}

	if (Soldier->FirstWaypoint != nullptr)
	{
		SetWaypoint(Soldier->FirstWaypoint->GetActorLocation());

	}
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
