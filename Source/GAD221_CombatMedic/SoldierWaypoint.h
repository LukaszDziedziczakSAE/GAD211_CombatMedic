// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoldierWaypoint.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API ASoldierWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoldierWaypoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int WaveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<enum ESoldierSide> Side;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int GetWaveIndex() { return WaveIndex; }

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<ESoldierSide> GetSide() { return Side; }
};
