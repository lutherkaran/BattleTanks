// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto rotation = RelativeSpeed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	auto rawRotaion = GetRelativeRotation().Yaw + rotation;
	SetRelativeRotation(FRotator(0.f, rawRotaion, 0.f));
}
