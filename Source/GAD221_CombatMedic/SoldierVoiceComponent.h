// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoldierVoiceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAD221_COMBATMEDIC_API USoldierVoiceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USoldierVoiceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* CombatStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* CombatEnd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* CombatInProgress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* GotHit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* Healed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* GruntingLoop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* GruntingPositive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* GruntingNegative;

	UFUNCTION()
	void Play(USoundBase* Sound);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASoldier* Soldier;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void PlayCombatStart();

	UFUNCTION(BlueprintCallable)
	void PlayCombatEnd();

	UFUNCTION(BlueprintCallable)
	void PlayCombatInProgress();
	
	UFUNCTION(BlueprintCallable)
	void PlayGotHit();

	UFUNCTION(BlueprintCallable)
	void PlayHealed();

	UFUNCTION(BlueprintCallable)
	void PlayGruntingLoop();

	UFUNCTION(BlueprintCallable)
	void PlayGruntingPositive();

	UFUNCTION(BlueprintCallable)
	void PlayGruntingNegative();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPlayGrunting;
		
};
