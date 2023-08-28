// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimComponent.h"
#include "TankBarrel.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AimComponent = CreateDefaultSubobject<UTankAimComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector Location)
{
	auto ourTank = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *ourTank, *Location.ToString())
	AimComponent->AimAt(Location,LaunchSpeed);
}

void ATank::SetupBarrel(UTankBarrel* TankBarrel)
{
	AimComponent->SetupBarrel(TankBarrel);
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

