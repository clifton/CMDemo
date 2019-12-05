#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/ObjectMacros.h"
#include "AbilitySystemComponent.h"
#include "CMCharacterAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class ACMCharacter;

UCLASS()
class CRIMSONMIRROR_API UCMCharacterAttributeSet : public UAttributeSet
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internal")
	ACMCharacter* WhoAttackedUsLast;
	
public:
	//Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = RPGAttributes, meta = (HideFromModifiers))
		FGameplayAttributeData Health;
	UFUNCTION()
		void OnRep_Health() { GAMEPLAYATTRIBUTE_REPNOTIFY(UCMCharacterAttributeSet, Health); }
	ATTRIBUTE_ACCESSORS(UCMCharacterAttributeSet, Health)
		UFUNCTION(BlueprintCallable, Category = RPGAttributes)
		float OWSGetHealth() const
	{
		return Health.GetCurrentValue();
	}
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		void OWSSetHealth(float NewVal)
	{
		UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
		if (ensure(AbilityComp))
		{
			AbilityComp->SetNumericAttributeBase(GetHealthAttribute(), NewVal);
		};
	}
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		void OWSInitHealth(float NewVal)
	{
		Health.SetBaseValue(NewVal);
		Health.SetCurrentValue(NewVal);
	}

	//MaxHealth
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
		FGameplayAttributeData MaxHealth;
	UFUNCTION()
		void OnRep_MaxHealth() { GAMEPLAYATTRIBUTE_REPNOTIFY(UCMCharacterAttributeSet, MaxHealth); }
	ATTRIBUTE_ACCESSORS(UCMCharacterAttributeSet, MaxHealth)
		UFUNCTION(BlueprintCallable, Category = RPGAttributes)
		float OWSGetMaxHealth() const
	{
		return MaxHealth.GetCurrentValue();
	}
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		void OWSSetMaxHealth(float NewVal)
	{
		UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
		if (ensure(AbilityComp))
		{
			AbilityComp->SetNumericAttributeBase(GetMaxHealthAttribute(), NewVal);
		};
	}
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		void OWSInitMaxHealth(float NewVal)
	{
		MaxHealth.SetBaseValue(NewVal);
		MaxHealth.SetCurrentValue(NewVal);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TransientAttribute", meta = (HideFromLevelInfos))
	FGameplayAttributeData	Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TransientAttribute", meta = (HideFromLevelInfos))
	FGameplayAttributeData	Healing;

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
