// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierCombat.h"
#include "Soldier.h"
#include "SoldierAIController.h"
#include "SoldierWaypoint.h"
#include "Kismet/KismetMathLibrary.h"
#include "CombatMedicGameMode.h"

// Sets default values for this component's properties
USoldierCombat::USoldierCombat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USoldierCombat::BeginPlay()
{
	Super::BeginPlay();

	Soldier = Cast<ASoldier>(GetOwner());
	
}


// Called every frame
void USoldierCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USoldierCombat::SetFightingPosition(ASoldierWaypoint* Waypoint)
{
	if (Waypoint == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing ASoldierWaypoint reference in SoldierCombat for setting FightingPosition"));
		return;
	}

	FightingPosition = Waypoint;
	if (Soldier == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Soldier reference in SoldierCombat"));
		return;
	}
	if (Soldier->SoldierAI() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Soldier AI reference in SoldierCombat"));
		return;
	}
		
	Soldier->SoldierAI()->SetWaypoint(FightingPosition->GetActorLocation());
}

void USoldierCombat::ClearWaypoint()
{
	FightingPosition = nullptr;
}

void USoldierCombat::Fire()
{
	if (Opponent == nullptr) return;

	float Random = UKismetMathLibrary::RandomFloatInRange(0, 1);

	if (Random <= ChanceToHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s hit %s"), *Soldier->GetName(), *Opponent->GetName());
		Opponent->SetRandomInjury();

		if (Soldier->SoldierSide == Allied)
		{
			Cast<ACombatMedicGameMode>(GetWorld()->GetAuthGameMode())->TryEndCombat();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missed %s"), *Soldier->GetName(), *Opponent->GetName());
	}
}

bool USoldierCombat::OpponentIsDown()
{
	if (Opponent == nullptr) return true;

	return Opponent->IsDowned();


}

void USoldierCombat::SetOpponentSoldier(ASoldier* OpponentSoldier)
{
	if (Opponent == OpponentSoldier) return;

	Opponent = OpponentSoldier;
	UE_LOG(LogTemp, Warning, TEXT("%s set opponent to %s"), *Soldier->GetName(), *OpponentSoldier->GetName());

	if (Soldier->SoldierAI() != nullptr)
	{
		Soldier->SoldierAI()->SetOpponent(Opponent);
	}
}

void USoldierCombat::LookAtOpponent()
{
	if (Opponent == nullptr) return;

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Soldier->GetActorLocation(), Opponent->GetActorLocation());

	Soldier->SetActorRotation(LookAtRot, ETeleportType::TeleportPhysics);
}

bool USoldierCombat::TrySetOpponent()
{
	if (Opponent != nullptr) return true;
	if (FightingPosition == nullptr) return false;

	for (ASoldierWaypoint* CombatWaypoint : FightingPosition->TargetFightingPositions)
	{
		if (CombatWaypoint->SoldierInOverlap != nullptr && !CombatWaypoint->SoldierInOverlap->IsDowned())
		{
			SetOpponentSoldier(CombatWaypoint->SoldierInOverlap);
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Did not find opponent"));
	return false;
}

void USoldierCombat::EndCombat()
{
	Opponent = nullptr;
	FightingPosition = nullptr;
}

