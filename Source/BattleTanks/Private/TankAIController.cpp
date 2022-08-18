// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	AIControlledTank = GetAIControlledTank();
	playerTank = GetPlayerControlledTank();

	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO AI TANK FOUND"))
	}
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO PLAYER FOUND"))
	}

}
void ATankAIController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("PLAYER FOUND AT: %s"), *(playerTank->GetActorLocation().ToString()))
	if (AIControlledTank)
	{
		AIControlledTank->AimAt(playerTank->GetActorLocation());
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
