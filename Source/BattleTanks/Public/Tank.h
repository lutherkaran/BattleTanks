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

	UFUNCTION(BlueprintCallable, Category = SetupBarrel)
		void SetupBarrel(UTankBarrel* TankBarrel);

	UFUNCTION(BlueprintCallable, Category = SetupTurret)
		void SetupTurret(UTankTurret* TankTurret);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup);
	TSubclassOf<AProjectile> ProjectileBlueprint; /*specific to projectil blueprint reference */ //UClass* ProjectileBlueprint // all classes; 

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	float LastFireTIme = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimComponent* AimComponent;

	UTankBarrel* Barrel = nullptr;

	/*UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent;*/
};
