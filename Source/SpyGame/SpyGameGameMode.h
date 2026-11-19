#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpyGameGameMode.generated.h"

UCLASS()
class SPYGAME_API ASpyGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASpyGameGameMode();

protected:
	virtual void BeginPlay() override;
};
