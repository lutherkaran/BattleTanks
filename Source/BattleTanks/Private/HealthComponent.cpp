// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
	IsAlive = true;
	AActor* owner = GetOwner();
	if (owner)
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}

}

void UHealthComponent::BeginPlay() {
	Super::BeginPlay();

}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//int32 DamagePoints = FPlatformMath::RoundToInt(Damage);

	DealDamage(Damage);
	//return DamageToApply;
}

void UHealthComponent::DealDamage(float DamageAmount)
{
	if (DamageAmount <= 0) return;

	auto DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		IsAlive = false;
		OnDeath.Broadcast();
	}
}

float UHealthComponent::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}


