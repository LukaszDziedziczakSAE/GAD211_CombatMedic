// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EBodyPart
{
	None UMETA(DisplayName = "None"),
	Torso UMETA(DisplayName = "Torso"),
	Head UMETA(DisplayName = "Head"),
	Neck UMETA(DisplayName = "Neck"),
	LeftShoulder UMETA(DisplayName = "Left Shoulder"),
	RightShoulder UMETA(DisplayName = "Right Shoulder"),
	LeftArm UMETA(DisplayName = "Left Arm"),
	RightArm UMETA(DisplayName = "Right Arm"),
	LeftHip UMETA(DisplayName = "Left Hip"),
	RightHip UMETA(DisplayName = "Right Hip"),
	LeftLeg UMETA(DisplayName = "Left Leg"),
	RightLeg UMETA(DisplayName = "Right Leg")
};
