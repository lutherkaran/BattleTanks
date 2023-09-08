// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//AimComponent = CreateDefaultSubobject<UTankAimComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::AimAt(FVector Location)
{
	if (!ensure(AimComponent)) return;
	AimComponent->AimAt(Location, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) return;
	bool isReloded = (FPlatformTime::Seconds() - LastFireTIme) > ReloadTimeInSeconds;
	if (isReloded) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTIme = FPlatformTime::Seconds();
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

