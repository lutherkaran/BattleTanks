// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimComponent::UTankAimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimComponent::SetupBarrel(UTankBarrel* TankBarrel)
{
	this->Barrel = TankBarrel;
}
void UTankAimComponent::AimAt(FVector HitLocation, float _LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity(this, OutVelocity, StartLocation, HitLocation, _LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveProjectileVelocity)
	{
		auto AimDirection = OutVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString())
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimComponent::MoveBarrelTowards(FVector _AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = _AimDirection.Rotation();
	auto DeltaRotator = BarrelRotator - AimAsRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *DeltaRotator.ToString())
}
// Called when the game starts
void UTankAimComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}
// Called every frame
void UTankAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

