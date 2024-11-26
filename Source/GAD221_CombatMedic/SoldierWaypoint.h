// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Soldier.h"
#include "SoldierWaypoint.generated.h"

UENUM(BlueprintType)
enum EWaypointType
{
	Travel,
	FightingPosition
};


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
	int Index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ESoldierSide> Side;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CrouchingAmmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EWaypointType> WaypointType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* Proximity;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int GetIndex() { return Index; }

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<ESoldierSide> GetSide() { return Side; }

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EWaypointType> GetWaypointType() { return WaypointType; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ASoldier* SoldierInOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ASoldierWaypoint*> TargetFightingPositions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ASoldier* AssignedSoldier;

	UFUNCTION(BlueprintCallable)
	FVector RandomPointInRadius();
};
