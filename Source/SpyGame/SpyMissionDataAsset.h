#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpyGameTypes.h"
#include "SpyMissionDataAsset.generated.h"

UCLASS(BlueprintType)
class SPYGAME_API USpyMissionDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MissionTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Briefing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSpyMissionObjective> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSpyDialogueLine> Dialogue;
};
