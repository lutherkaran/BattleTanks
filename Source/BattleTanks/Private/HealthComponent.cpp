// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Initiailize();
}

bool UHealthComponent::Initiailize()
{
	CurrentHealth = Health;
	IsAlive = true;
	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
		return true;
	}
	return false;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	DealDamage(Damage);
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
	return (float)CurrentHealth / (float)Health;
}


