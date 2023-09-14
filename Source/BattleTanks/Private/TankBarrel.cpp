// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto elevation = RelativeSpeed * MaxDegreesPersecond * GetWorld()->DeltaTimeSeconds;
	auto rawElevation = GetRelativeRotation().Pitch + elevation;
	rawElevation = FMath::Clamp<float>(rawElevation, MinElevationPersecond, MaxElevationPersecond);
	SetRelativeRotation(FRotator(rawElevation, 0.f, 0.f));
}
