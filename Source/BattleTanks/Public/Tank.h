// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable)
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup);
	TSubclassOf<AProjectile> ProjectileBlueprint; /*specific to projectil blueprint reference */ //UClass* ProjectileBlueprint // all classes; 
	
	float LastFireTIme = 0;

protected:
	UPROPERTY(BlueprintReadOnly)
		UTankAimComponent* AimComponent;

	UTankBarrel* Barrel = nullptr; // TODO Remove

	/*UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent;*/
private:
	virtual void BeginPlay() override;
};
