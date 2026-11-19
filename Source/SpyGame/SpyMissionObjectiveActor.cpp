#include "SpyMissionObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "SpyMissionSubsystem.h"
#include "SpyGameCharacter.h"

ASpyMissionObjectiveActor::ASpyMissionObjectiveActor()
{
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->InitSphereRadius(160.0f);
	RootComponent = Trigger;

	ObjectiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectiveMesh"));
	ObjectiveMesh->SetupAttachment(RootComponent);
	ObjectiveMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (Cube.Succeeded())
	{
		ObjectiveMesh->SetStaticMesh(Cube.Object);
	}
	ObjectiveMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 1.2f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASpyMissionObjectiveActor::OnOverlap);
}

void ASpyMissionObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	if (USpyMissionSubsystem* Mission = GetWorld()->GetSubsystem<USpyMissionSubsystem>())
	{
		Mission->OnMissionChanged.AddLambda([this](int32) {
			SetActorHiddenInGame(false);
		});
	}
}

void ASpyMissionObjectiveActor::OnOverlap(UPrimitiveComponent*, AActor* OtherActor,
	UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!Cast<ASpyGameCharacter>(OtherActor))
	{
		return;
	}

	USpyMissionSubsystem* Mission = GetWorld()->GetSubsystem<USpyMissionSubsystem>();
	if (!Mission)
	{
		return;
	}
	if (bRequiresOtherObjectives && !Mission->AreNonExtractionObjectivesComplete())
	{
		return;
	}
	if (Mission->CompleteObjective(ObjectiveIndex))
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}
