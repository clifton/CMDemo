#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "CMFloatingCombatText.generated.h"


UCLASS()
class CRIMSONMIRROR_API UCMFloatingCombatText : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage);
};
