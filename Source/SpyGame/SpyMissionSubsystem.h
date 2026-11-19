#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpyGameTypes.h"
#include "SpyMissionSubsystem.generated.h"

class USpyMissionDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpyMissionChanged, int32, ObjectiveIndex);

UCLASS()
class SPYGAME_API USpyMissionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FSpyMissionChanged OnMissionChanged;

	UFUNCTION(BlueprintCallable)
	void InitializeMission();

	UFUNCTION(BlueprintCallable)
	bool CompleteObjective(int32 ObjectiveIndex);

	UFUNCTION(BlueprintCallable)
	bool IsObjectiveComplete(int32 ObjectiveIndex) const;

	UFUNCTION(BlueprintCallable)
	bool AreNonExtractionObjectivesComplete() const;

	UFUNCTION(BlueprintCallable)
	FText GetCurrentObjectiveText() const;

	UFUNCTION(BlueprintPure)
	ESpyMissionStatus GetMissionStatus() const;

	static USpyMissionDataAsset* CreateDefaultMissionAsset(UObject* Outer);

private:
	FText MissionTitle;
	FText Briefing;
	TArray<FSpyMissionObjective> Objectives;
	ESpyMissionStatus MissionStatus = ESpyMissionStatus::Briefing;
};
