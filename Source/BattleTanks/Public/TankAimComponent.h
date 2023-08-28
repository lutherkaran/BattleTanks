// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

class UTankBarrel; //Forward Declaration
class UTankTurret;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANKS_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimComponent();
	
	void SetupBarrel(UTankBarrel* _Barrel);
	void SetupTurret(UTankTurret* Turret);

	void AimAt(FVector Location, float _LaunchSpeed);
	void MoveBarrelTowards(FVector _AimDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
