#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "CMGameSession.generated.h"


UCLASS()
class CRIMSONMIRROR_API ACMGameSession : public AGameSession
{
	GENERATED_BODY()
	
	virtual void RegisterServer() override;
};
