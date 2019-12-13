#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQuery.h"
#include "CMEnvQueryManager.generated.h"


UCLASS()
class CRIMSONMIRROR_API UCMEnvQueryManager : public UEnvQueryManager
{
	GENERATED_BODY()
	
public:
	// basically the same as RunEQSQuery but takes custom parameters
	UFUNCTION(BlueprintCallable, Category = "AI|EQS", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "WrapperClass"))
	static UEnvQueryInstanceBlueprintWrapper* CMRunEQSQuery(
		UObject* WorldContextObject, UEnvQuery* QueryTemplate, UObject* Querier, TEnumAsByte<EEnvQueryRunMode::Type> RunMode,
		TSubclassOf<UEnvQueryInstanceBlueprintWrapper> WrapperClass, TMap<FName, float> QueryParams);
};
