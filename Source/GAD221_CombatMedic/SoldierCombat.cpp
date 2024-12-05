// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierCombat.h"
#include "Soldier.h"
#include "SoldierAIController.h"
#include "SoldierWaypoint.h"
#include "Kismet/KismetMathLibrary.h"
#include "CombatMedicGameMode.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SoldierVoiceComponent.h"

// Sets default values for this component's properties
USoldierCombat::USoldierCombat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void USoldierCombat::BeginPlay()
{
	Super::BeginPlay();

	Soldier = Cast<ASoldier>(GetOwner());
	ChanceToHitBase = ChanceToHit;
	
	MuzzleFlash = Cast<UNiagaraComponent>(Soldier->GetComponentsByTag(UNiagaraComponent::StaticClass(), TEXT("MuzzleFlash"))[0]);
	if (MuzzleFlash == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s did not find muzzle flash"), *Soldier->GetActorNameOrLabel());
	}

	FireIndex = FireRate;
}


// Called every frame
void USoldierCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BurstIndex >= 0)
	{
		if (FireIndex >= FireRate) Fire();
		else FireIndex += DeltaTime;
	}
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
	
	FightingPosition->AssignedSoldier = Soldier;
	Soldier->SoldierAI()->SetFightingPosition(FightingPosition->GetActorLocation());
}

void USoldierCombat::ClearWaypoint()
{
	FightingPosition = nullptr;
}

void USoldierCombat::Fire()
{
	if (Opponent == nullptr || FightingPosition->SoldierInOverlap != Soldier) return;

	if (Opponent->IsDowned() || Soldier->IsDowned())
	{
		ClearOpponent();
		return;
	}

	if (BurstIndex == 0)
	{
		float Random = UKismetMathLibrary::RandomFloatInRange(0, 1);
		if (Random <= ChanceToHit)
		{
			UE_LOG(LogTemp, Display, TEXT("%s hit %s"), *Soldier->GetActorNameOrLabel(), *Opponent->GetActorNameOrLabel());
			Opponent->SetRandomInjury();

			if (Soldier->SoldierSide == Allied)
			{
				Soldier->GameMode->TryEndCombat();
			}

			else if (Soldier->SoldierSide == Enemy)
			{
			}

			Opponent = nullptr;
			Soldier->Voice->PlayCombatHitEnemy();
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("%s missed %s"), *Soldier->GetActorNameOrLabel(), *Opponent->GetActorNameOrLabel());
		}

		ChanceToHit += ChanceToHitIncreasePerShot;
		
	}

	if (MuzzleFlash != nullptr) MuzzleFlash->Activate(true);

	if (WeaponFireSound != nullptr && MuzzleFlash != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFireSound, MuzzleFlash->GetComponentLocation());
	}

	if (Soldier->GetCrouching() < CrouchingThreshhold)
	{
		Soldier->PlayAnimMontage(StandingShotMontage);
	}
	else
	{
		Soldier->PlayAnimMontage(CrouchingShotMontage);
	}

	FireIndex = 0;
	BurstIndex--;
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
	UE_LOG(LogTemp, Warning, TEXT("%s set opponent to %s"), *Soldier->GetActorNameOrLabel(), *OpponentSoldier->GetActorNameOrLabel());

	if (Soldier->SoldierAI() != nullptr)
	{
		Soldier->SoldierAI()->SetOpponent(Opponent);
	}
}

void USoldierCombat::ClearOpponent()
{
	Opponent = nullptr;
}

void USoldierCombat::LookAtOpponent()
{
	if (Opponent == nullptr) return;

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Soldier->GetActorLocation(), Opponent->GetActorLocation());

	Soldier->SetActorRotation(LookAtRot, ETeleportType::TeleportPhysics);
}

bool USoldierCombat::TrySetOpponent()
{
	if (Opponent != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s already has opponent"), *Soldier->GetActorNameOrLabel());
		return true;
	}
	if (FightingPosition == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s FightingPosition missing"), *Soldier->GetActorNameOrLabel());
		return false;
	}

	if (Soldier->SoldierSide == Allied && Soldier->GameMode->AllEnemySoldiersDown()) return false;
	if (Soldier->SoldierSide == Enemy && Soldier->GameMode->AllAlliesDown()) return false;

	if (FightingPosition->TargetFightingPositions.Num() == 0)
	{
		SetOpponentSoldier(NearestEnemySoldier());
		return Opponent != nullptr;
	}
	
	else
	{
		int MaxLoop = 1000;
		int Loop = 0;

		while (Loop < MaxLoop)
		{
			for (ASoldierWaypoint* CombatWaypoint : FightingPosition->TargetFightingPositions)
			{
				if (CombatWaypoint->AssignedSoldier != nullptr && !CombatWaypoint->AssignedSoldier->IsDowned())
				{
					SetOpponentSoldier(CombatWaypoint->AssignedSoldier);
					return true;
				}
			}
			Loop++;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("%s Did not find opponent"), *Soldier->GetActorNameOrLabel());
	return false;
}

void USoldierCombat::EndCombat()
{
	Opponent = nullptr;
	FightingPosition = nullptr;
	ResetChanceToHit();
}

void USoldierCombat::LookAtFirstFirePosition()
{
	if (FightingPosition == nullptr) return;
	if (FightingPosition->TargetFightingPositions.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s FightingPosition missing Targets"), *FightingPosition->GetActorNameOrLabel());
		return;
	}

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Soldier->GetActorLocation(), FightingPosition->TargetFightingPositions[0]->GetActorLocation());

	Soldier->SetActorRotation(LookAtRot, ETeleportType::TeleportPhysics);
}

void USoldierCombat::ResetChanceToHit()
{
	ChanceToHit = ChanceToHitBase;
}

void USoldierCombat::FireBurst()
{
	if (Opponent == nullptr && !TrySetOpponent())
	{
		return;
	}

	if (Opponent->IsDowned())
	{
		Opponent = nullptr;
		FireBurst();
	}

	LookAtOpponent();
	BurstIndex = UKismetMathLibrary::RandomIntegerInRange(0, BurstTotal);
	FireIndex = 0;
}

ASoldier* USoldierCombat::NearestEnemySoldier()
{
	TArray<AActor*> SoldierActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoldier::StaticClass(), SoldierActors);
	TArray<ASoldier*> Enemies;
	for (AActor* SoldierActor : SoldierActors)
	{
		ASoldier* ListSoldier = Cast<ASoldier>(SoldierActor);
		if (ListSoldier == nullptr || 
			ListSoldier->SoldierSide == Soldier->SoldierSide ||
			!ListSoldier->IsAlive() ||
			!ListSoldier->IsDowned()
			) continue;

		Enemies.Add(ListSoldier);
	}

	ASoldier* NearestSoldier = nullptr;
	float NearestSoldierDistance = 100000.0f;
	for (ASoldier* Enemy : Enemies)
	{
		float Distance = FVector::Distance(Enemy->GetActorLocation(), Soldier->GetActorLocation());

		if (NearestSoldier == nullptr)
		{
			NearestSoldier = Enemy;
			NearestSoldierDistance = Distance;
		}

		else if (Distance < NearestSoldierDistance)
		{
			NearestSoldier = Enemy;
			NearestSoldierDistance = Distance;
		}
	}

	return NearestSoldier;
}

