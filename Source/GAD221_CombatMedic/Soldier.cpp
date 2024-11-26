// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerMedic.h"
#include "MedicInteraction.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "SoldierCombat.h"
#include "SoldierAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "CombatMedicGameMode.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASoldier::ASoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionProximity = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Proximity"));
	InteractionProximity->SetupAttachment(GetRootComponent());
	InteractionProximity->SetRelativeLocation(FVector{ -95, 0, 0});
	InteractionProximity->SetSphereRadius(80);
	InteractionProximity->OnComponentBeginOverlap.AddDynamic(this, &ASoldier::OnOverlapBegin);
	InteractionProximity->OnComponentEndOverlap.AddDynamic(this, &ASoldier::OnOverlapEnd);
	InteractionProximity->SetCanEverAffectNavigation(false);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector{ -110.000000, 20.000000, 30.000000});
	CameraComponent->SetRelativeRotation(FQuat::MakeFromEuler(FVector{0, -80, -90}));

	TorsoColider = CreateDefaultSubobject<UBoxComponent>(TEXT("Torso Colider"));
	TorsoColider->SetupAttachment(GetMesh(), TEXT("spine_02"));
	TorsoColider->SetCollisionProfileName(TEXT("NoCollision"));
	TorsoColider->SetBoxExtent(FVector{ 25, 20,16 });
	TorsoColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	TorsoColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TorsoColider->SetCanEverAffectNavigation(false);

	NeckColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Neck Colider"));
	NeckColider->SetupAttachment(GetMesh(), TEXT("neck_01"));
	NeckColider->SetCollisionProfileName(TEXT("NoCollision"));
	NeckColider->SetCapsuleHalfHeight(12);
	NeckColider->SetCapsuleRadius(8);
	NeckColider->SetRelativeLocation(FVector{5,0,0});
	NeckColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	NeckColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	NeckColider->SetCanEverAffectNavigation(false);

	HeadColider = CreateDefaultSubobject<USphereComponent>(TEXT("Head Colider"));
	HeadColider->SetupAttachment(GetMesh(), TEXT("head"));
	HeadColider->SetCollisionProfileName(TEXT("NoCollision"));
	HeadColider->SetSphereRadius(14);
	HeadColider->SetRelativeLocation(FVector{ 12,0,0 });
	HeadColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	HeadColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	HeadColider->SetCanEverAffectNavigation(false);

	RightShoulderColider = CreateDefaultSubobject<USphereComponent>(TEXT("Right Shoulder Colider"));
	RightShoulderColider->SetupAttachment(GetMesh(), TEXT("upperarm_r"));
	RightShoulderColider->SetCollisionProfileName(TEXT("NoCollision"));
	RightShoulderColider->SetSphereRadius(14);
	RightShoulderColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	RightShoulderColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightShoulderColider->SetCanEverAffectNavigation(false);

	RightArmColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Right Arm Colider"));
	RightArmColider->SetupAttachment(GetMesh(), TEXT("lowerarm_r"));
	RightArmColider->SetCollisionProfileName(TEXT("NoCollision"));
	RightArmColider->SetCapsuleHalfHeight(36);
	RightArmColider->SetCapsuleRadius(12);
	RightArmColider->SetRelativeRotation(FQuat::MakeFromEuler(FVector{ 0, 90, 9 }));
	RightArmColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	RightArmColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightArmColider->SetCanEverAffectNavigation(false);

	LeftShoulderColider = CreateDefaultSubobject<USphereComponent>(TEXT("Left Shoulder Colider"));
	LeftShoulderColider->SetupAttachment(GetMesh(), TEXT("upperarm_l"));
	LeftShoulderColider->SetCollisionProfileName(TEXT("NoCollision"));
	LeftShoulderColider->SetSphereRadius(14);
	LeftShoulderColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	LeftShoulderColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftShoulderColider->SetCanEverAffectNavigation(false);

	LeftArmColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Left Arm Colider"));
	LeftArmColider->SetupAttachment(GetMesh(), TEXT("lowerarm_l"));
	LeftArmColider->SetCollisionProfileName(TEXT("NoCollision"));
	LeftArmColider->SetCapsuleHalfHeight(36);
	LeftArmColider->SetCapsuleRadius(12);
	LeftArmColider->SetRelativeRotation(FQuat::MakeFromEuler(FVector{ 0, -90, 9 }));
	LeftArmColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	LeftArmColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftArmColider->SetCanEverAffectNavigation(false);

	RightHipColider = CreateDefaultSubobject<USphereComponent>(TEXT("Right Hip Colider"));
	RightHipColider->SetupAttachment(GetMesh(), TEXT("thigh_r"));
	RightHipColider->SetCollisionProfileName(TEXT("NoCollision"));
	RightHipColider->SetSphereRadius(14);
	RightHipColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	RightHipColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightHipColider->SetCanEverAffectNavigation(false);

	RightLegColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Right Leg Colider"));
	RightLegColider->SetupAttachment(GetMesh(), TEXT("calf_r"));
	RightLegColider->SetCollisionProfileName(TEXT("NoCollision"));
	RightLegColider->SetCapsuleHalfHeight(36);
	RightLegColider->SetCapsuleRadius(12);
	RightLegColider->SetRelativeRotation(FQuat::MakeFromEuler(FVector{ 0, 90, 9 }));
	RightLegColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	RightLegColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightLegColider->SetCanEverAffectNavigation(false);

	LeftHipColider = CreateDefaultSubobject<USphereComponent>(TEXT("Left Hip Colider"));
	LeftHipColider->SetupAttachment(GetMesh(), TEXT("thigh_l"));
	LeftHipColider->SetCollisionProfileName(TEXT("NoCollision"));
	LeftHipColider->SetSphereRadius(14);
	LeftHipColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	LeftHipColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftHipColider->SetCanEverAffectNavigation(false);

	LeftLegColider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Left Leg Colider"));
	LeftLegColider->SetupAttachment(GetMesh(), TEXT("calf_l"));
	LeftLegColider->SetCollisionProfileName(TEXT("NoCollision"));
	LeftLegColider->SetCapsuleHalfHeight(36);
	LeftLegColider->SetCapsuleRadius(12);
	LeftLegColider->SetRelativeRotation(FQuat::MakeFromEuler(FVector{0, -90, 9}));
	LeftLegColider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	LeftLegColider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftLegColider->SetCanEverAffectNavigation(false);

	Combat = CreateDefaultSubobject<USoldierCombat>(TEXT("Combat"));

	TorsoBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Torso Bleed"));
	TorsoBleed->SetupAttachment(GetMesh(), TEXT("spine_02"));
	TorsoBleed->bAutoActivate = false;

	NeckBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Neck Bleed"));
	NeckBleed->SetupAttachment(GetMesh(), TEXT("neck_01"));
	NeckBleed->bAutoActivate = false;

	HeadBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Head Bleed"));
	HeadBleed->SetupAttachment(GetMesh(), TEXT("head"));
	HeadBleed->bAutoActivate = false;

	RightShoulderBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Right Shoulder Bleed"));
	RightShoulderBleed->SetupAttachment(GetMesh(), TEXT("upperarm_r"));
	RightShoulderBleed->bAutoActivate = false;

	RightArmBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Right Arm Bleed"));
	RightArmBleed->SetupAttachment(GetMesh(), TEXT("lowerarm_r"));
	RightArmBleed->bAutoActivate = false;

	LeftShoulderBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Left Shoulder Bleed"));
	LeftShoulderBleed->SetupAttachment(GetMesh(), TEXT("upperarm_l"));
	LeftShoulderBleed->bAutoActivate = false;

	LeftArmBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Left Arm Bleed"));
	LeftArmBleed->SetupAttachment(GetMesh(), TEXT("lowerarm_l"));
	LeftArmBleed->bAutoActivate = false;

	RightHipBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Right Hip Bleed"));
	RightHipBleed->SetupAttachment(GetMesh(), TEXT("thigh_r"));
	RightHipBleed->bAutoActivate = false;

	RightLegBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Right Leg Bleed"));
	RightLegBleed->SetupAttachment(GetMesh(), TEXT("calf_r"));
	RightLegBleed->bAutoActivate = false;

	LeftHipBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Left Hip Bleed"));
	LeftHipBleed->SetupAttachment(GetMesh(), TEXT("thigh_l"));
	LeftHipBleed->bAutoActivate = false;

	LeftLegBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Left Leg Bleed"));
	LeftLegBleed->SetupAttachment(GetMesh(), TEXT("calf_l"));
	LeftLegBleed->bAutoActivate = false;

	DeathBleed = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Death Bleed"));
	DeathBleed->SetupAttachment(GetMesh(), TEXT("spine_02"));
	DeathBleed->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ASoldier::BeginPlay()
{
	Super::BeginPlay();

	AI = Cast<ASoldierAIController>(GetController());

	if (SoldierSide == Enemy)
	{
		bIsInCombat = true;
	}
	AdjustMovementSpeed();
}

void ASoldier::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsDowned || !bIsAlive || SoldierSide != Allied) return;

	APlayerMedic* Player = Cast<APlayerMedic>(OtherActor);
	if (Player == nullptr) return;

	Player->MedicInteraction->Patient = this;
}

void ASoldier::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsDowned || !bIsAlive || SoldierSide != Allied) return;

	APlayerMedic* Player = Cast<APlayerMedic>(OtherActor);
	if (Player == nullptr) return;

	if (Player->MedicInteraction->Patient == this) Player->MedicInteraction->Patient = nullptr;
}

void ASoldier::AdjustMovementSpeed()
{
	if (Crouching > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = CrouchingWalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = bIsInCombat ? RunningSpeed : WalkingSpeed;
	}
}

// Called every frame
void ASoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsAlive) return;

	if (Injury.BodyPart != None)
	{
		CurrentHealth = FMath::Clamp( (CurrentHealth - (Injury.CurrentAmount / 60) * DeltaTime * InjuryHealthLossMultiplier), 0, MaxHealth);

		if (CurrentHealth == 0)
		{
			Death();
		}
	}

	else
	{
		if (CurrentHealth < MaxHealth)
		{
			CurrentHealth = FMath::Clamp(CurrentHealth + (HealthRecoveryRate * DeltaTime), 0, MaxHealth);
		}

		if (CurrentPain > 0)
		{
			CurrentPain = FMath::Clamp((CurrentPain - (PainRecoveryRate * DeltaTime)), 0, MaxPain);
		}

		if (bIsDowned && CurrentPain < PainThreshhold)
		{
			bIsDowned = false;
			AI->SetIsDowned(bIsDowned);
			Cast<ACombatMedicGameMode>(GetWorld()->GetAuthGameMode())->TryEndCombat();
		}
	}
}

// Called to bind functionality to input
void ASoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASoldier::SetInjury(FInjury NewInjury)
{
	/*if (bHasBeenInjured) return;
	bHasBeenInjured = true;*/
	Injury = NewInjury;
	bIsDowned = true;
	if (AI != nullptr) AI->SetIsDowned(bIsDowned);
	StartBleeding(Injury.BodyPart);
	float HealthDeduction = UKismetMathLibrary::RandomFloatInRange(100.0f, 200.0f);
	CurrentHealth = FMath::Clamp((CurrentHealth - HealthDeduction), 0.0f, MaxHealth);

	float PainDeduction = UKismetMathLibrary::RandomFloatInRange(50.0f, 100.0f);
	CurrentPain = FMath::Clamp((CurrentPain + PainDeduction), 0.0f, MaxPain);
}

void ASoldier::SetRandomInjury()
{
	FInjury NewInjury;
	NewInjury.GenerateNew();
	SetInjury(NewInjury);
}

TEnumAsByte<EBodyPart> ASoldier::BodyPartFromShape(UShapeComponent* Shape)
{
	if (Shape == TorsoColider) return EBodyPart::Torso;
	else if (Shape == NeckColider) return EBodyPart::Neck;
	else if (Shape == HeadColider) return EBodyPart::Head;
	else if (Shape == LeftShoulderColider) return EBodyPart::LeftShoulder;
	else if (Shape == LeftArmColider) return EBodyPart::LeftArm;
	else if (Shape == RightShoulderColider) return EBodyPart::RightShoulder;
	else if (Shape == RightArmColider) return EBodyPart::RightArm;
	else if (Shape == LeftHipColider) return EBodyPart::LeftHip;
	else if (Shape == LeftLegColider) return EBodyPart::LeftLeg;
	else if (Shape == RightHipColider) return EBodyPart::RightHip;
	else if (Shape == RightLegColider) return EBodyPart::RightLeg;

	return EBodyPart::None;
}

void ASoldier::HealInjury(float Amount)
{
	Injury.CurrentAmount = FMath::Clamp(Injury.CurrentAmount - Amount, 0, Injury.MaxAmount);

	if (Injury.CurrentAmount == 0)
	{
		Injury.BodyPart = None;
		StopAllBleeding();
	}
}

void ASoldier::HealPain(float Amount)
{
	CurrentPain = FMath::Clamp(CurrentPain - Amount, 0, MaxPain);
}

void ASoldier::SetCrouching(float Value)
{
	Crouching = Value;
	AdjustMovementSpeed();
}

void ASoldier::EngageCombat(ASoldierWaypoint* FightingPosition)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s combat start"), *GetName());
	
	bIsInCombat = true;
	if (AI != nullptr) AI->SetIsInCombat(bIsInCombat);
	else UE_LOG(LogTemp, Error, TEXT("%s missing AI"), *GetName());
	Combat->SetFightingPosition(FightingPosition);
	AdjustMovementSpeed();
}

void ASoldier::DisengageCombat()
{
	bIsInCombat = false;
	AI->SetIsInCombat(bIsInCombat);
	Combat->EndCombat();
	AI->GoToLastWaypointSet();
	AdjustMovementSpeed();
}

void ASoldier::StopAllBleeding()
{
	TorsoBleed->Deactivate();
	NeckBleed->Deactivate();
	HeadBleed->Deactivate();
	RightShoulderBleed->Deactivate();
	RightArmBleed->Deactivate();
	LeftShoulderBleed->Deactivate();
	LeftArmBleed->Deactivate();
	RightHipBleed->Deactivate();
	RightLegBleed->Deactivate();
	LeftHipBleed->Deactivate();
	LeftLegBleed->Deactivate();
}

void ASoldier::StartBleeding(TEnumAsByte<EBodyPart> BodyPart)
{
	switch (BodyPart)
	{
	case Torso:
		TorsoBleed->Activate();
		break;

	case Neck:
		NeckBleed->Activate();
		break;

	case Head:
		HeadBleed->Activate();
		break;

	case RightShoulder:
		RightShoulderBleed->Activate();
		break;

	case RightArm:
		RightArmBleed->Activate();
		break;

	case LeftShoulder:
		LeftShoulderBleed->Activate();
		break;

	case LeftArm:
		LeftArmBleed->Activate();
		break;

	case RightHip:
		RightHipBleed->Activate();
		break;

	case RightLeg:
		RightLegBleed->Activate();
		break;

	case LeftHip:
		LeftHipBleed->Activate();
		break;

	case LeftLeg:
		LeftLegBleed->Activate();
		break;

	}
}

void ASoldier::Death()
{
	if (!bIsAlive) return;
	bIsAlive = false;

	StopAllBleeding();

	TArray<USkeletalMeshComponent*> ChildrenComponents;
	GetComponents<USkeletalMeshComponent>(ChildrenComponents);

	GetMesh()->Stop();

	FVector DeathLocation = GetMesh()->GetRelativeLocation();
	DeathLocation.Z -= 5;
	GetMesh()->SetRelativeLocation(DeathLocation);

	DeathBleed->Activate();
}

void ASoldier::FireWeapon_Implementation()
{

}

