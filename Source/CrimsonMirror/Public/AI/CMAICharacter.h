#pragma once

#include "CoreMinimal.h"
#include "CMCharacter.h"
#include "CMAICharacter.generated.h"


UCLASS()
class CRIMSONMIRROR_API ACMAICharacter : public ACMCharacter
{
	GENERATED_BODY()

public:
	ACMAICharacter(const class FObjectInitializer& ObjectInitializer);
	
protected:
	// Actual hard pointer to AbilitySystemComponent
	UPROPERTY(BlueprintReadOnly, Category = "AbilitySystemComponent")
	class UCMAbilitySystemComponent* HardRefAbilitySystemComponent;

	// Actual hard pointer to AttributeSetBase
	UPROPERTY(BlueprintReadOnly, Category = "CharacterAttributeSet")
	class UCMCharacterAttributeSet* HardRefCharacterAttributeSet;

	virtual void BeginPlay() override;

	FDelegateHandle HealthChangedDelegateHandle;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	// Tag change callbacks
	virtual void LoseControlTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
