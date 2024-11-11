// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierWaypoint.h"
#include "Components/SphereComponent.h"


// Sets default values
ASoldierWaypoint::ASoldierWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Proximity = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Proximity"));
	Proximity->SetupAttachment(GetRootComponent());
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

}

void ASoldierWaypoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ASoldierWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

