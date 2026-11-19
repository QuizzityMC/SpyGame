#include "SpyTechDemoMapActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMeshActor.h"
#include "SpyMissionObjectiveActor.h"

ASpyTechDemoMapActor::ASpyTechDemoMapActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpyTechDemoMapActor::BeginPlay()
{
	Super::BeginPlay();

	SpawnBox(FVector(0.0f, 0.0f, -50.0f), FVector(30.0f, 30.0f, 1.0f));
	SpawnBox(FVector(-1500.0f, 0.0f, 500.0f), FVector(1.0f, 30.0f, 10.0f));
	SpawnBox(FVector(1500.0f, 0.0f, 500.0f), FVector(1.0f, 30.0f, 10.0f));
	SpawnBox(FVector(0.0f, -1500.0f, 500.0f), FVector(30.0f, 1.0f, 10.0f));
	SpawnBox(FVector(0.0f, 1500.0f, 500.0f), FVector(30.0f, 1.0f, 10.0f));
	SpawnBox(FVector(-500.0f, -300.0f, 400.0f), FVector(1.0f, 8.0f, 8.0f));
	SpawnBox(FVector(300.0f, 500.0f, 300.0f), FVector(8.0f, 1.0f, 6.0f));
	SpawnMissionActors();
}

void ASpyTechDemoMapActor::SpawnBox(FVector Location, FVector Scale)
{
	AStaticMeshActor* Box = GetWorld()->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(), Location, FRotator::ZeroRotator);
	if (Box)
	{
		UStaticMeshComponent* Mesh = Box->GetStaticMeshComponent();
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
		if (Cube.Succeeded())
		{
			Mesh->SetStaticMesh(Cube.Object);
		}
		Box->SetActorScale3D(Scale);
		Mesh->SetMobility(EComponentMobility::Static);
		Box->SetActorEnableCollision(true);
	}
}

void ASpyTechDemoMapActor::SpawnMissionActors()
{
	const FVector Locations[] = {
		FVector(-1200.0f, 0.0f, 100.0f),
		FVector(700.0f, 0.0f, 100.0f),
		FVector(900.0f, -700.0f, 100.0f),
		FVector(1200.0f, 700.0f, 100.0f)
	};

	for (int32 Index = 0; Index < 4; ++Index)
	{
		FActorSpawnParameters Params;
		ASpyMissionObjectiveActor* Objective = GetWorld()->SpawnActor<ASpyMissionObjectiveActor>(
			ASpyMissionObjectiveActor::StaticClass(), Locations[Index], FRotator::ZeroRotator, Params);
		if (Objective)
		{
			Objective->ObjectiveIndex = Index;
			Objective->bRequiresOtherObjectives = (Index == 3);
		}
	}
}
