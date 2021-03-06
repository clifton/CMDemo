#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CMAIController.generated.h"


UCLASS()
class CRIMSONMIRROR_API ACMAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACMAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
