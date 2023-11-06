// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "HealthComponent.h"
// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = false;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(HealthComponent)) return;
}