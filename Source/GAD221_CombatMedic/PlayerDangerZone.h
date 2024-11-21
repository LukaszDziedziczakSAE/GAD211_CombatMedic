// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerDangerZone.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API APlayerDangerZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerDangerZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int FightIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Proximity;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ACombatMedicGameMode* GameMode;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
