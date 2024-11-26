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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float ChanceToHitBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UNiagaraComponent* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage* StandingShotMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAnimMontage* CrouchingShotMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* WeaponFireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int BurstIndex{ -1 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int BurstTotal{ 4 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FireRate{ 0.1f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float FireIndex{ 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CrouchingThreshhold{ 0.5f };

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceToHit{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChanceToHitIncreasePerShot{ 0.0005 };

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

	UFUNCTION(BlueprintCallable)
	void LookAtFirstFirePosition();

	UFUNCTION(BlueprintCallable)
	void ResetChanceToHit();

	UFUNCTION(BlueprintCallable)
	void FireBurst();
};
