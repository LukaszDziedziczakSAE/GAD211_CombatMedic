// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatMedicGameMode.h"
#include "Soldier.h"
#include "SoldierWaypoint.h"
#include "Kismet/GameplayStatics.h"
#include "SoldierAIController.h"

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

}
