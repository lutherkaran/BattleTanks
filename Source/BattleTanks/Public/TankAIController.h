// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 *
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float _deltaTime) override;

	ATank* GetAIControlledTank() const;
	ATank* GetPlayerControlledTank() const;

	ATank* AIControlledTank;
	ATank* playerTank;
};
