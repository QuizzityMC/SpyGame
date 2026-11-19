#include "SpyMissionSubsystem.h"
#include "SpyMissionDataAsset.h"

void USpyMissionSubsystem::InitializeMission()
{
	USpyMissionDataAsset* Mission = CreateDefaultMissionAsset(this);
	MissionTitle = Mission->MissionTitle;
	Briefing = Mission->Briefing;
	Objectives = Mission->Objectives;
	MissionStatus = ESpyMissionStatus::InProgress;
}

bool USpyMissionSubsystem::CompleteObjective(int32 ObjectiveIndex)
{
	if (!Objectives.IsValidIndex(ObjectiveIndex) || Objectives[ObjectiveIndex].bComplete)
	{
		return false;
	}
	if (ObjectiveIndex == Objectives.Num() - 1 && !AreNonExtractionObjectivesComplete())
	{
		return false;
	}

	Objectives[ObjectiveIndex].bComplete = true;
	OnMissionChanged.Broadcast(ObjectiveIndex);

	if (ObjectiveIndex == Objectives.Num() - 1)
	{
		MissionStatus = ESpyMissionStatus::Complete;
	}
	return true;
}

bool USpyMissionSubsystem::IsObjectiveComplete(int32 ObjectiveIndex) const
{
	return Objectives.IsValidIndex(ObjectiveIndex) && Objectives[ObjectiveIndex].bComplete;
}

bool USpyMissionSubsystem::AreNonExtractionObjectivesComplete() const
{
	for (int32 Index = 0; Index < Objectives.Num() - 1; ++Index)
	{
		if (!Objectives[Index].bComplete)
		{
			return false;
		}
	}
	return Objectives.Num() > 1;
}

FText USpyMissionSubsystem::GetCurrentObjectiveText() const
{
	if (MissionStatus == ESpyMissionStatus::Complete)
	{
		return FText::FromString(TEXT("Mission complete"));
	}
	for (const FSpyMissionObjective& Objective : Objectives)
	{
		if (!Objective.bComplete)
		{
			return Objective.Title;
		}
	}
	return FText::FromString(TEXT("Reach extraction"));
}

ESpyMissionStatus USpyMissionSubsystem::GetMissionStatus() const
{
	return MissionStatus;
}

USpyMissionDataAsset* USpyMissionSubsystem::CreateDefaultMissionAsset(UObject* Outer)
{
	USpyMissionDataAsset* Mission = NewObject<USpyMissionDataAsset>(Outer);
	Mission->MissionTitle = FText::FromString(TEXT("Operation Glass Crown"));
	Mission->Briefing = FText::FromString(
		TEXT("An old enemy is converting Meridian Station's power core into a covert targeting system. "
		     "Enter through the service wing, steal the access cipher, disable the jammer, and extract."));

	Mission->Objectives = {
		{FText::FromString(TEXT("Enter the service wing")), false},
		{FText::FromString(TEXT("Recover the Glass Crown cipher")), false},
		{FText::FromString(TEXT("Disable the signal jammer")), false},
		{FText::FromString(TEXT("Reach the extraction helipad")), false}
	};

	Mission->Dialogue = {
		{FText::FromString(TEXT("Control")), FText::FromString(TEXT("Meridian Station is closed to the public. Use the service entrance."))},
		{FText::FromString(TEXT("Control")), FText::FromString(TEXT("The cipher is in the east vault. Keep your eyes on the cameras."))},
		{FText::FromString(TEXT("Agent Vale")), FText::FromString(TEXT("One more signal and Glass Crown goes dark."))}
	};
	return Mission;
}
