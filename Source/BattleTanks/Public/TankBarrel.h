// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float _degrees);
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPersecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationPersecond = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationPersecond = 0;
};
