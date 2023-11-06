// Fill out your copyright notice in the Description page of Project Settings.


#include "Tests/HealthComponentTest.h"
#include "Misc/AutomationTest.h"
#include "TankAimComponent.h"
#include "Tank.h"
#include "HealthComponent.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnPlayerTest, "Gameplay.Health.Player.Spawn Player and Health Component is Attached", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNegativePlayerHealthTest, "Gameplay.Health.Player.Health is never negative", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::MediumPriority | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDecreaseHealthTest, "Gameplay.Health.Player.Apply Damage", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCannotIncreaseHealthTest, "Gameplay.Health.Player. Try to cheat and Increase Health", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::HighPriority | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FKillPlayerTest, "Gameplay.Health.Player.Kill Player", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)


bool FSpawnPlayerTest::RunTest(const FString& parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		ATank* Tank = World->SpawnActor<ATank>();
		UHealthComponent* HealthComponent = Tank->GetHealthComponent();
	}
	return true;
}

bool FNegativePlayerHealthTest::RunTest(const FString& parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	if (World)
	{
		ATank* Tank = World->SpawnActor<ATank>();
		UHealthComponent* HealthComponent = Tank->GetHealthComponent();
		if (!HealthComponent) return false;
		HealthComponent->DealDamage(HealthComponent->GetMaxHealth() + 50);
		TestEqual("Player Health Should Never Be Negative", HealthComponent->GetCurrentHealth(), 0.f);
	}

	return true;
}

bool FDecreaseHealthTest::RunTest(const FString& parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	if (World)
	{
		ATank* Tank = World->SpawnActor<ATank>();
		UHealthComponent* HealthComponent = Tank->GetHealthComponent();
		if (!HealthComponent) return false;
		HealthComponent->DealDamage(40);
		TestEqual("Decrease Health Test", HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth() - 40);
	}
	return true;
}

bool FCannotIncreaseHealthTest::RunTest(const FString& parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	if (World)
	{
		ATank* Tank = World->SpawnActor<ATank>();
		UHealthComponent* HealthComponent = Tank->GetHealthComponent();
		if (!HealthComponent) return false;
		HealthComponent->DealDamage(-50);
		TestEqual("Should Not Increase Health", HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
	}
	return true;
}

bool FKillPlayerTest::RunTest(const FString& parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	if (World)
	{
		ATank* Tank = World->SpawnActor<ATank>();
		UHealthComponent* HealthComponent = Tank->GetHealthComponent();
		if (!HealthComponent) return false;
		HealthComponent->DealDamage(HealthComponent->GetMaxHealth());
		TestEqual("Player Must Die if all of its health is Taken", HealthComponent->IsPlayerAlive(), false);
	}
	return true;
}

HealthComponentTest::HealthComponentTest()
{

}

HealthComponentTest::~HealthComponentTest()
{

}
