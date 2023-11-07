// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Health")
		class UHealthComponent* HealthComponent;

	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }

private:
	// Sets default values for this pawn's properties
	ATank();
};
