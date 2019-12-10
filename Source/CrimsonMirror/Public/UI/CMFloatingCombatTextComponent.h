#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "CMFloatingCombatTextComponent.generated.h"


UCLASS()
class CRIMSONMIRROR_API UCMFloatingCombatTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage);
};
