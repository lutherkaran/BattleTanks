// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 *
 */
class ATank;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 1000;

	UFUNCTION()
	void OnPossessedTankDeath();
};
