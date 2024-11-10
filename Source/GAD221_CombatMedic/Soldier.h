// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FInjury.h"
#include "Soldier.generated.h"

UENUM(BlueprintType)
enum ESoldierSide
{
	Allied,
	Enemy
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FInjury Injury;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth{ 1000.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth{ 1000.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkingSpeed{ 200 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunningSpeed{ 600 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrouchingWalkSpeed{ 180 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* TorsoColider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* NeckColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* HeadColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* RightShoulderColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* RightArmColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* LeftShoulderColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* LeftArmColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* RightHipColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* RightLegColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* LeftHipColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* LeftLegColider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* TopMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Bottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Shoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Arms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Vest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* VestAccesories;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Belt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Helmet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* KneepadL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* KneepadR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Headset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* HelmetStrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Goggles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Weapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool IsDowned() { return bIsDowned; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UFUNCTION(BlueprintCallable)
	void SetInjury(FInjury NewInjury);

	UFUNCTION(BlueprintCallable)
	void SetRandomInjury();

	UFUNCTION(BlueprintCallable)
	FInjury GetInjury() { return Injury; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SoldierName{TEXT("SoldierName")};

	UFUNCTION(BlueprintPure)
	float HealthPercentage() { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EBodyPart> BodyPartFromShape(UShapeComponent* Shape);

	UFUNCTION(BlueprintCallable)
	void HealInjury(float Amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ASoldierWaypoint* FightingPosition1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasBeenInjured;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ESoldierSide> SoldierSide;


};
