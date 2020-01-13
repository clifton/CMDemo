#include "AI/CMEnvQueryManager.h"
#include "VisualLogger/VisualLogger.h"
#include "GameFramework/Controller.h"


UEnvQueryInstanceBlueprintWrapper* UCMEnvQueryManager::CMRunEQSQuery(
	UObject* WorldContextObject, UEnvQuery* QueryTemplate, UObject* Querier, TEnumAsByte<EEnvQueryRunMode::Type> RunMode,
	TSubclassOf<UEnvQueryInstanceBlueprintWrapper> WrapperClass, TMap<FName, float> QueryParams)
{
	if (QueryTemplate == nullptr || Querier == nullptr)
	{
		return nullptr;
	}

	TArray<FAIDynamicParam> AIQueryParams;
	QueryTemplate->CollectQueryParams(*Querier, AIQueryParams);

	UEnvQueryManager* EQSManager = GetCurrent(WorldContextObject);
	UEnvQueryInstanceBlueprintWrapper* QueryInstanceWrapper = nullptr;

	if (EQSManager)
	{
		bool bValidQuerier = true;

		// convert controller-owners to pawns, unless specifically configured not to do so
		if (GET_AI_CONFIG_VAR(bAllowControllersAsEQSQuerier) == false && Cast<AController>(Querier))
		{
			AController* Controller = Cast<AController>(Querier);
			if (Controller->GetPawn())
			{
				Querier = Controller->GetPawn();
			}
			else
			{
				UE_VLOG(Controller, LogEQS, Error, TEXT("Trying to run EQS query while not having a pawn! Aborting."));
				bValidQuerier = false;
			}
		}

		if (bValidQuerier)
		{
			QueryInstanceWrapper = NewObject<UEnvQueryInstanceBlueprintWrapper>(EQSManager, (UClass*)(WrapperClass) ? (UClass*)WrapperClass : UEnvQueryInstanceBlueprintWrapper::StaticClass());
			check(QueryInstanceWrapper);

			TArray<FEnvNamedValue> EnvNamedValueParams;
			FEnvQueryRequest QueryRequest(QueryTemplate, Querier);

			for (auto Param : AIQueryParams)
			{
				if (QueryParams.Contains(Param.ParamName))
				{
					Param.Value = QueryParams[Param.ParamName];
					FEnvNamedValue EnvParam;
					EnvParam.Value = Param.Value;
					EnvParam.ParamName = Param.ParamName;
					EnvNamedValueParams.Add(EnvParam);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Not enough parameters to run query in CMRunEQSQuery! Missing key: %s"), *Param.ParamName.ToString());
				}
			}
			QueryRequest.SetNamedParams(EnvNamedValueParams);
			QueryInstanceWrapper->SetInstigator(WorldContextObject);
			QueryInstanceWrapper->RunQuery(RunMode, QueryRequest);
		}
	}

	return QueryInstanceWrapper;
}
