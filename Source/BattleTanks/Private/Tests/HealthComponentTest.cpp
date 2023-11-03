// Fill out your copyright notice in the Description page of Project Settings.


#include "Tests/HealthComponentTest.h"
#include "Misc/AutomationTest.h"
#include "TankAimComponent.h"
#include "Tank.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnPlayerTest, "Gameplay.Health.Player.Spawn Player", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNegativePlayerHealthTest, "Gameplay.Health.Player.Health is never negative", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::MediumPriority | EAutomationTestFlags::ProductFilter)
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDecreaseHealthTest, "Gameplay.Health.Player.Apply Damage", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCannotIncreaseHealthTest, "Gameplay.Health.Player. Try to cheat and Increase Health", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::HighPriority | EAutomationTestFlags::ProductFilter)
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FKillPlayerTest, "Gameplay.Health.Player.Kill Player", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)


bool FSpawnPlayerTest::RunTest(const FString& parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		ATank* tank = World->SpawnActor<ATank>();
		if (!tank) {
			return false;
		}
	}
	return true;
}
//bool FSpawnPlayerTest::RunTest(const FString& parameters)
//{
//
//}
//bool FSpawnPlayerTest::RunTest(const FString& parameters)
//{
//
//}
//bool FSpawnPlayerTest::RunTest(const FString& parameters)
//{
//
//}

HealthComponentTest::HealthComponentTest()
{
}

HealthComponentTest::~HealthComponentTest()
{
}
