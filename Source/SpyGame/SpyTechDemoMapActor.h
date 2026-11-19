#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpyTechDemoMapActor.generated.h"

UCLASS()
class SPYGAME_API ASpyTechDemoMapActor : public AActor
{
	GENERATED_BODY()

public:
	ASpyTechDemoMapActor();

protected:
	virtual void BeginPlay() override;

private:
	void SpawnBox(FVector Location, FVector Scale);
	void SpawnMissionActors();
};
