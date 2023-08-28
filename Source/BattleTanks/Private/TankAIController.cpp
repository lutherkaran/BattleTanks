// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	AIControlledTank = GetAIControlledTank();
	PlayerControlledTank = GetPlayerControlledTank();

	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO AI TANK FOUND"))
	}
	if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO PLAYER FOUND"))
	}

}
void ATankAIController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
	if (AIControlledTank)
	{
		if (PlayerControlledTank) {
			AIControlledTank->AimAt(PlayerControlledTank->GetActorLocation());
			//UE_LOG(LogTemp, Warning, TEXT("PLAYER FOUND AT: %s"), *(PlayerControlledTank->GetActorLocation().ToString()))
		}
	}
}
ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
