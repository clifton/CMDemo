#pragma once

#include "CoreMinimal.h"
#include "Items/CMItem.h"
#include "Items/CMEquippableItem.h"
#include "CMWeaponItem.generated.h"


UCLASS()
class CRIMSONMIRROR_API UCMWeaponItem : public UCMEquippableItem
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	UCMWeaponItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	float AttackDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	float AttackBaseDamage;

	/** Weapon actor to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> WeaponActor;
};
