// Fill out your copyright notice in the Description page of Project Settings.



#include<TankAimComponent.h>
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimComponent>();

	if (!ensure(AimingComponent)) return;

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float _deltatime) {
	Super::Tick(_deltatime);
	AimTowardsCrossahir();
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

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
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
