// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDangerZone.h"
#include "CombatMedicGameMode.h"
#include "PlayerMedic.h"
#include "Components/BoxComponent.h"

// Sets default values
APlayerDangerZone::APlayerDangerZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Proximity = CreateDefaultSubobject<UBoxComponent>(TEXT("Proximity"));
	SetRootComponent(Proximity);
	Proximity->OnComponentBeginOverlap.AddDynamic(this, &APlayerDangerZone::OnOverlapBegin);
	Proximity->SetCanEverAffectNavigation(false);
	Proximity->SetBoxExtent(FVector{ 600, 200, 100 });
}

// Called when the game starts or when spawned
void APlayerDangerZone::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ACombatMedicGameMode>(GetWorld()->GetAuthGameMode());
}

void APlayerDangerZone::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerMedic* PlayerMedic = Cast<APlayerMedic>(OtherActor);
	if (PlayerMedic != nullptr && GameMode != nullptr && GameMode->GetCombatIndex() == FightIndex)
	{
		GameMode->PlayerEnteredDangerZone();
	}
}

// Called every frame
void APlayerDangerZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

