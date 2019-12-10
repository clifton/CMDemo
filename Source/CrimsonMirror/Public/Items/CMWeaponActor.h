#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMWeaponActor.generated.h"


class ACMCharacter;
class UCMWeaponItem;

UCLASS()
class CRIMSONMIRROR_API ACMWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMWeaponActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	ACMCharacter* Character;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	UCMWeaponItem* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float WeaponDelay;

protected:
	virtual void BeginPlay() override;

};
