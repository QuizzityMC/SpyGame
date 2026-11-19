#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "SpyMissionSubsystem.h"
#include "SpyMissionDataAsset.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpyMissionDataTest,
	"SpyGame.Mission.DefaultStoryIsComplete",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSpyMissionDataTest::RunTest(const FString& Parameters)
{
	USpyMissionDataAsset* Mission = USpyMissionSubsystem::CreateDefaultMissionAsset(GetTransientPackage());
	TestNotNull(TEXT("Default mission asset exists"), Mission);
	TestEqual(TEXT("Mission title"), Mission->MissionTitle.ToString(), FString(TEXT("Operation Glass Crown")));
	TestEqual(TEXT("Objective count"), Mission->Objectives.Num(), 4);
	TestTrue(TEXT("Briefing contains infiltration goal"), Mission->Briefing.ToString().Contains(TEXT("Enter")));
	TestTrue(TEXT("Mission has dialogue"), Mission->Dialogue.Num() >= 3);
	return true;
}

#endif
