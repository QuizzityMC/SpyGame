#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpyGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SPYGAME_API ASpyGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpyGameCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FollowCamera;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Interact();
};
