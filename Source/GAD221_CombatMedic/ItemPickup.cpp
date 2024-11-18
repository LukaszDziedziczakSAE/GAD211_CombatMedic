// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "Components/SphereComponent.h"
#include "PlayerMedic.h"
#include "MedicInteraction.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemPickup::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItemPickup::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemPickup::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerMedic* Player = Cast<APlayerMedic>(OtherActor);
	if (Player == nullptr) return;

	Player->MedicInteraction->ItemPickup = this;
}

void AItemPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerMedic* Player = Cast<APlayerMedic>(OtherActor);
	if (Player == nullptr) return;

	if (Player->MedicInteraction->ItemPickup == this) Player->MedicInteraction->ItemPickup = nullptr;
}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

