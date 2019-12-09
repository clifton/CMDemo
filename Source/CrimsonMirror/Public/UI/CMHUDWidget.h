#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMHUDWidget.generated.h"


UCLASS()
class CRIMSONMIRROR_API UCMHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetRespawnCountdown(float RespawnTimeRemaining);
	
	/**
	* Attribute setters
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthPercentage(float HealthPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetHealthRegenRate(float HealthRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxStamina(float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentStamina(float CurrentStamina);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetStaminaPercentage(float StaminaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetStaminaRegenRate(float StaminaRegenRate);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxMana(float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMana(float CurrentMana);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaPercentage(float ManaPercentage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetManaRegenRate(float ManaRegenRate);
};
