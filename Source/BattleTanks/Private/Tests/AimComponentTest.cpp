// Fill out your copyright notice in the Description page of Project Settings.


#include "Tests/AimComponentTest.h"
#include "Misc/AutomationTest.h"
#include "TankAimComponent.h"
#include "Tank.h"
#include "Tests/AutomationEditorCommon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnPlayer, "Gameplay.Aim.Player.Spawn Player", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)

bool FSpawnPlayer::RunTest(const FString& Params)
{
	UWorld* world = FAutomationEditorCommonUtils::CreateNewMap();
	{
		ATank* Tank = world->SpawnActor<ATank>();
		if (!Tank)
		{
			return false;
		}
	}
	return true;
}

AimComponentTest::AimComponentTest()
{
}

AimComponentTest::~AimComponentTest()
{
}
