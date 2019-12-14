#include "CMEngineSubsystem.h"
#include "AbilitySystemGlobals.h"


void UCMEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 4.24 requires we initialize the data cache
	UAbilitySystemGlobals::Get().InitGlobalData();
}
