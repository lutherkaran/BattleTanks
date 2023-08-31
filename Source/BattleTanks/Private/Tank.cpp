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
	AimComponent = CreateDefaultSubobject<UTankAimComponent>(FName("Aiming Component"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::AimAt(FVector Location)
{
	AimComponent->AimAt(Location, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloded = (FPlatformTime::Seconds() - LastFireTIme) > ReloadTimeInSeconds;
	if (Barrel && isReloded) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTIme = FPlatformTime::Seconds();
	}
}

void ATank::SetupBarrel(UTankBarrel* TankBarrel)
{
	AimComponent->SetupBarrel(TankBarrel);
	Barrel = TankBarrel;
}

void ATank::SetupTurret(UTankTurret* TankTurret)
{
	AimComponent->SetupTurret(TankTurret);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

