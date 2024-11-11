// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierWaypoint.h"
#include "Components/SphereComponent.h"
#include "Soldier.h"
#include "SoldierAIController.h"


// Sets default values
ASoldierWaypoint::ASoldierWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Proximity = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Proximity"));
	SetRootComponent(Proximity);
	//Proximity->SetupAttachment(GetRootComponent());
	Proximity->SetSphereRadius(50);
	Proximity->OnComponentBeginOverlap.AddDynamic(this, &ASoldierWaypoint::OnOverlapBegin);
	Proximity->OnComponentEndOverlap.AddDynamic(this, &ASoldierWaypoint::OnOverlapEnd);
	Proximity->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void ASoldierWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoldierWaypoint::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASoldier* Soldier = Cast<ASoldier>(OtherActor);
	if (Soldier == nullptr || SoldierInOverlap == Soldier) return;

	

	SoldierInOverlap = Soldier;

	if (WaypointType == Travel)
	{
		Soldier->SoldierAI()->ArrivedAtWaypoint(Index);
	}
	else if (WaypointType == FightingPosition)
	{
		Soldier->SetCrouching(CrouchingAmmount);
		UE_LOG(LogTemp, Warning, TEXT("%s entered %s"), *Soldier->GetName(), *GetName());
	}
}

void ASoldierWaypoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASoldier* Soldier = Cast<ASoldier>(OtherActor);
	if (Soldier == nullptr || Soldier->IsInCombat() || SoldierInOverlap == nullptr) return;
	
	if (SoldierInOverlap == Soldier) SoldierInOverlap = nullptr;

	if (WaypointType == FightingPosition)
	{
		Soldier->SetCrouching(0);
		UE_LOG(LogTemp, Warning, TEXT("%s exited %s"), *Soldier->GetName(), *GetName());
	}
}

// Called every frame
void ASoldierWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

