// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierCombat.h"
#include "Soldier.h"
#include "Kismet/KismetMathLibrary.h"

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

void USoldierCombat::Fire()
{
	if (Opponent == nullptr) return;

	float Random = UKismetMathLibrary::RandomFloatInRange(0, 1);

	if (Random <= ChanceToHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s hit %s"), *Soldier->GetName(), *Opponent->GetName());
		Opponent->SetRandomInjury();
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

