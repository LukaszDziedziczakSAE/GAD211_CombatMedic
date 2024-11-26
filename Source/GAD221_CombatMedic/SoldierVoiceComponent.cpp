// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierVoiceComponent.h"
#include "Components/AudioComponent.h"
#include "Soldier.h"

// Sets default values for this component's properties
USoldierVoiceComponent::USoldierVoiceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USoldierVoiceComponent::BeginPlay()
{
	Super::BeginPlay();

	Soldier = Cast<ASoldier>(GetOwner());
	
}


void USoldierVoiceComponent::Play(USoundBase* Sound)
{
	if (Sound == nullptr || Soldier == nullptr || Soldier->SoldierSide != Allied) return;

	if (Soldier->VoiceAudioComponent->IsPlaying()) Soldier->VoiceAudioComponent->Stop();
	Soldier->VoiceAudioComponent->SetSound(Sound);
	Soldier->VoiceAudioComponent->Play();
}

// Called every frame
void USoldierVoiceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bPlayGrunting && !Soldier->VoiceAudioComponent->IsPlaying())
	{
		PlayGruntingLoop();
	}

	else if (Soldier->VoiceAudioComponent->IsPlaying() && Soldier->VoiceAudioComponent->Sound == GruntingLoop && !bPlayGrunting)
	{
		Soldier->VoiceAudioComponent->Stop();
	}
}

void USoldierVoiceComponent::PlayCombatStart()
{
	Play(CombatStart);
}

void USoldierVoiceComponent::PlayCombatEnd()
{
	Play(CombatEnd);
}

void USoldierVoiceComponent::PlayCombatInProgress()
{
	Play(CombatInProgress);
}

void USoldierVoiceComponent::PlayGotHit()
{
	Play(GotHit);
}

void USoldierVoiceComponent::PlayHealed()
{
	Play(Healed);
}

void USoldierVoiceComponent::PlayGruntingLoop()
{
	Play(GruntingLoop);
}

void USoldierVoiceComponent::PlayGruntingPositive()
{
	Play(GruntingPositive);
}

void USoldierVoiceComponent::PlayGruntingNegative()
{
	Play(GruntingNegative);
}

