// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerMedic.h"
#include "MedicInteraction.h"

// Sets default values
ASoldier::ASoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionProximity = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Proximity"));
	InteractionProximity->SetupAttachment(GetRootComponent());
	InteractionProximity->OnComponentBeginOverlap.AddDynamic(this, &ASoldier::OnOverlapBegin);
	InteractionProximity->OnComponentEndOverlap.AddDynamic(this, &ASoldier::OnOverlapEnd);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASoldier::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoldier::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsDowned) return;

	APlayerMedic* Player = Cast<APlayerMedic>(OtherActor);
	if (Player == nullptr) return;

	Player->MedicInteraction->Patient = this;
}

void ASoldier::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsDowned) return;
	APlayerMedic* Player = Cast<APlayerMedic>(OtherActor);
	if (Player == nullptr) return;

	if (Player->MedicInteraction->Patient == this) Player->MedicInteraction->Patient = nullptr;
}

// Called every frame
void ASoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

