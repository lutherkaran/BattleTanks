// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto AIControlledTank = GetAIControlledTank();
	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO AI TANK FOUND"))
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("AI CONTROLLED TANKS ARE: %s"), *(AIControlledTank->GetName()))
	//}
}
void ATankAIController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
	auto playerTank = GetPlayerControlledTank();
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO PLAYER FOUND"))
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PLAYER FOUND: %s at %s"), *(playerTank->GetName()), *(playerTank->GetActorLocation().ToString()))
	//}
}