// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Soldier.generated.h"

UCLASS()
class GAD221_COMBATMEDIC_API ASoldier : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoldier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDowned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* InteractionProximity;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool IsDowned() { return bIsDowned; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;
};
