#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CMGameModeBase.generated.h"


UCLASS()
class CRIMSONMIRROR_API ACMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

public:
	ACMGameModeBase();

	virtual void StartPlay() override;
};
