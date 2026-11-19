#pragma once

#include "CoreMinimal.h"
#include "SpyGameTypes.generated.h"

UENUM(BlueprintType)
enum class ESpyMissionStatus : uint8
{
	Briefing,
	InProgress,
	Complete
};

USTRUCT(BlueprintType)
struct FSpyDialogueLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Speaker = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Line = FText::GetEmpty();
};

USTRUCT(BlueprintType)
struct FSpyMissionObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bComplete = false;
};
