#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMCharacterStatusBarWidget.generated.h"


class ACMCharacter;

UCLASS()
class CRIMSONMIRROR_API UCMCharacterStatusBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCMCharacterStatusBarWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Target)
	ACMCharacter* TargetCharacter;

	UPROPERTY(EditDefaultsOnly, Category = Target)
	float MaxRenderDistance;

	UPROPERTY(EditDefaultsOnly, Category = Target)
	float MinimumScaleVisible;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthPercentage(float HealthPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPercentage(float ManaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCharacterName(const FText& NewName);

	UFUNCTION(BlueprintCallable)
	float GetRenderScale();

	UFUNCTION(BlueprintCallable)
	bool bShouldRenderCheckDistance();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTargeted();

	UFUNCTION(BlueprintImplementableEvent)
	void OnUntargeted();
};
