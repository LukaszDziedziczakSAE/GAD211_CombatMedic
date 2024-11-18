// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoldierCombat.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD221_COMBATMEDIC_API USoldierCombat : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USoldierCombat();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASoldier* Soldier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASoldierWaypoint* FightingPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ASoldier* Opponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceToHit{ 0 };

	UFUNCTION(BlueprintCallable)
	void SetFightingPosition(ASoldierWaypoint* Waypoint);

	UFUNCTION(BlueprintCallable)
	void ClearWaypoint();

	UFUNCTION(BlueprintPure)
	ASoldierWaypoint* GetFightingPosition(){ return FightingPosition; }

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintPure)
	bool OpponentIsDown();

	UFUNCTION(BlueprintCallable)
	void SetOpponentSoldier(ASoldier* OpponentSoldier);

	UFUNCTION(BlueprintCallable)
	void ClearOpponent();

	UFUNCTION(BlueprintCallable)
	void LookAtOpponent();

	UFUNCTION(BlueprintCallable)
	bool TrySetOpponent();

	UFUNCTION(BlueprintCallable)
	void EndCombat();
};
