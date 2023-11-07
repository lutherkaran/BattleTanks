// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankHealthDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();
	float CurrentHealth;

	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	FTankHealthDelegate OnDeath;

	// Sets default values for this component's properties
	UPROPERTY(EditDefaultsOnly, Category = "HealthComponent")
		float Health = 100;

	UPROPERTY(VisibleAnywhere, Category = "HealthComponent")
		bool IsAlive;

	UFUNCTION(BlueprintPure, Category = "HealthComponent")
		float GetHealthPercent() const;

	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() const { return Health; }
	FORCEINLINE bool IsPlayerAlive() const { return IsAlive; }

	virtual void BeginPlay() override;

	void DealDamage(float Damage);
	bool Initiailize();
};
