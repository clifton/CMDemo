#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CMGameModeBase.generated.h"


UCLASS(minimalapi)
class ACMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACMGameModeBase();

	void PlayerDied(AController* Controller);

protected:
	float RespawnDelay;

	TSubclassOf<class ACMPlayerCharacter> PlayerCharacterClass;

	AActor* EnemySpawnPoint;

	virtual void BeginPlay() override;

	void RespawnPlayer(AController* Controller);
};
