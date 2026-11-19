#include "SpyGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "SpyMissionSubsystem.h"
#include "Engine/World.h"

ASpyGameCharacter::ASpyGameCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

void ASpyGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (USpyMissionSubsystem* Mission = GetWorld()->GetSubsystem<USpyMissionSubsystem>())
	{
		Mission->InitializeMission();
	}
}

void ASpyGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASpyGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASpyGameCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ASpyGameCharacter::Interact);
}

void ASpyGameCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}

void ASpyGameCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}

void ASpyGameCharacter::Interact()
{
	FHitResult Hit;
	const FVector Start = GetActorLocation();
	const FVector End = Start + GetActorForwardVector() * 300.0f;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(SpyInteract), false, this);
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
}
