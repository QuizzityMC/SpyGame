#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpyMissionObjectiveActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class SPYGAME_API ASpyMissionObjectiveActor : public AActor
{
	GENERATED_BODY()

public:
	ASpyMissionObjectiveActor();

	UPROPERTY(EditAnywhere, Category = "Spy Mission")
	int32 ObjectiveIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Spy Mission")
	bool bRequiresOtherObjectives = false;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ObjectiveMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Trigger;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
