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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* TopMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Bottom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Shoes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Arms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Vest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* VestAccesories;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Belt;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Helmet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* KneepadL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* KneepadR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Headset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* HelmetStrap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Goggles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoldierCombat* Combat;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FireWeapon();
};
