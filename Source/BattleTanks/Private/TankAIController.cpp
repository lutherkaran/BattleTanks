// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}
void ATankAIController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	PlayerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AIControlledTank = Cast<ATank>(GetPawn());

	if (PlayerControlledTank)
	{
		AIControlledTank->AimAt(PlayerControlledTank->GetActorLocation());
		AIControlledTank->Fire();
		//UE_LOG(LogTemp, Warning, TEXT("PLAYER FOUND AT: %s"), *(PlayerControlledTank->GetActorLocation().ToString()))
	}
}

