#include "CMAssetManager.h"
#include "Items/CMItem.h"
#include "AbilitySystemGlobals.h"


const FPrimaryAssetType	UCMAssetManager::ConsumableItemType = TEXT("Consumable");
const FPrimaryAssetType	UCMAssetManager::SkillItemType = TEXT("Skill");
const FPrimaryAssetType	UCMAssetManager::TokenItemType = TEXT("Token");
const FPrimaryAssetType	UCMAssetManager::WeaponItemType = TEXT("Weapon");

UCMAssetManager& UCMAssetManager::Get()
{
	UCMAssetManager* This = Cast<UCMAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be CMAssetManager!"));
		return *NewObject<UCMAssetManager>(); // never calls this
	}
}

void UCMAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}


UCMItem* UCMAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UCMItem* LoadedItem = Cast<UCMItem>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}