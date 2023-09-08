// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

}
void ATankAIController::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	auto PlayerControlledTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AIControlledTank = (GetPawn());

	if (!ensure(PlayerControlledTank && AIControlledTank)) return;
	{
		MoveToActor(PlayerControlledTank, AcceptanceRadius);
		auto AimComponent = AIControlledTank->FindComponentByClass<UTankAimComponent>();
		if (!ensure(AimComponent)) { return; }
		AimComponent->AimAt(PlayerControlledTank->GetActorLocation());
		
		//AIControlledTank->Fire();
		//UE_LOG(LogTemp, Warning, TEXT("PLAYER FOUND AT: %s"), *(PlayerControlledTank->GetActorLocation().ToString()))
	}
}

