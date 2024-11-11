// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatStartTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
ACombatStartTrigger::ACombatStartTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Proximity = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Proximity"));
	Proximity->SetupAttachment(GetRootComponent());
	Proximity->OnComponentBeginOverlap.AddDynamic(this, &ACombatStartTrigger::OnOverlapBegin);
	Proximity->OnComponentEndOverlap.AddDynamic(this, &ACombatStartTrigger::OnOverlapEnd);
	Proximity->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void ACombatStartTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatStartTrigger::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ACombatStartTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ACombatStartTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

