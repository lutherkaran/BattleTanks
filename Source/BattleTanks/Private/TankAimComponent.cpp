// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimComponent.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

int UTankAimComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

// Called when the game starts
void UTankAimComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTIme = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RoundsLeft == 0) {
		FiringState = EFiringStatus::OutOfAmmo;
	}

	else if ((FPlatformTime::Seconds() - LastFireTIme) < ReloadTimeInSeconds) {
		FiringState = EFiringStatus::Reloading;
	}
	else if (isBarrelMoving()) {

		FiringState = EFiringStatus::Aiming;
	}
	else 
	{
		FiringState = EFiringStatus::Locked;
	}
}

EFiringStatus UTankAimComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity(this, OutVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveProjectileVelocity)
	{
		AimDirection = OutVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString())
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimComponent::Fire()
{
	if (FiringState == EFiringStatus::Locked || FiringState == EFiringStatus::Aiming) {
		if (!ensure(Barrel)) return;
		if (!ensure(ProjectileBlueprint)) return;
		{
			auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
			projectile->LaunchProjectile(LaunchSpeed);
			LastFireTIme = FPlatformTime::Seconds();
			RoundsLeft--;
		}
	}
}

void UTankAimComponent::MoveBarrelTowards(FVector _AimDirection)
{
	if (!ensure(Barrel || Turret)) return;

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = _AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	// Always yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	// Avoid going at the wrong direction
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *DeltaRotator.ToString())
}

bool UTankAimComponent::isBarrelMoving() {
	if (!ensure(Barrel)) { return false; }

	else
	{
		auto BarrelForward = Barrel->GetForwardVector();
		return BarrelForward.Equals(AimDirection, 0.01f);
	}
}

