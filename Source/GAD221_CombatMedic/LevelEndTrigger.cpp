// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEndTrigger.h"
#include "CombatMedicGameMode.h"
#include "Soldier.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelEndTrigger::ALevelEndTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Proximity = CreateDefaultSubobject<UBoxComponent>(TEXT("Proximity"));
	SetRootComponent(Proximity);
	Proximity->OnComponentBeginOverlap.AddDynamic(this, &ALevelEndTrigger::OnOverlapBegin);
	Proximity->SetCanEverAffectNavigation(false);
	Proximity->SetBoxExtent(FVector{ 600, 200, 100 });
}

// Called when the game starts or when spawned
void ALevelEndTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ACombatMedicGameMode>(GetWorld()->GetAuthGameMode());
}

void ALevelEndTrigger::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameMode == nullptr) return;

	ASoldier* Soldier = Cast<ASoldier>(OtherActor);
	if (Soldier != nullptr)
	{
		GameMode->SoldiersGotToLevelEnd();
	}
}

// Called every frame
void ALevelEndTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

