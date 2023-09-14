// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {

	Locked UMETA(DisplayName = "Locked"),
	Aiming UMETA(DisplayName = "Aiming"),
	Reloading UMETA(DisplayName = "Firing"),
	OutOfAmmo UMETA(DisplayName = "OutOfAmmo")
};

class UTankBarrel; //Forward Declaration
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANKS_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimComponent();

	void AimAt(FVector HitLocation);
	void MoveBarrelTowards(FVector _AimDirection);


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringState = EFiringStatus::Reloading;

	EFiringStatus GetFiringState() const;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = Firing)
		float ReloadTimeInSeconds = .5f;

	UPROPERTY(EditDefaultsOnly, Category = Setup);
	TSubclassOf<AProjectile> ProjectileBlueprint; /*specific to projectile blueprint reference */ //UClass* ProjectileBlueprint // all classes; 

	float LastFireTIme = 0;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
		void Fire();
	bool isBarrelMoving();

	FVector AimDirection = FVector(0);

	UPROPERTY(EditAnywhere, Category = "Firing")
		int32 RoundsLeft = 100;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetRoundsLeft() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
