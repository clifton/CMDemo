#pragma once

#include "CoreMinimal.h"
#include "Items/CMItem.h"
#include "CMWeaponItem.generated.h"


UCLASS()
class CRIMSONMIRROR_API UCMWeaponItem : public UCMItem
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	UCMWeaponItem();

	/** Weapon actor to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> WeaponActor;
};
