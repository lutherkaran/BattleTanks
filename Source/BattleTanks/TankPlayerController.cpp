// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
#include"TankAimComponent.h"
#include"Tank.h"
#include "HealthComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();

	if (!ensure(AimingComponent)) return;

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float _deltatime)
{
	Super::Tick(_deltatime);
	AimTowardsCrossahir();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;
		if (!ensure(PossessedTank->GetHealthComponent())) return;
		PossessedTank->GetHealthComponent()->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrossahir()
{
	if (!GetPawn()) return; // if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();

	if (!ensure(AimingComponent)) return;
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("HIT AT: %s"), *HitLocation.ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	//Find crosshair position in px coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(CrosshairXLocation * ViewPortSizeX, CrosshairYLocation * ViewPortSizeY);

	//De-projecting the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f, 0.f, 0.f);
	return false;

}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection));
}
