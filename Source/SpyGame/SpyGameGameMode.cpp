#include "SpyGameGameMode.h"
#include "SpyGameCharacter.h"
#include "SpyTechDemoMapActor.h"
#include "Engine/World.h"

ASpyGameGameMode::ASpyGameGameMode()
{
	DefaultPawnClass = ASpyGameCharacter::StaticClass();
}

void ASpyGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor<ASpyTechDemoMapActor>(
		ASpyTechDemoMapActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
}
