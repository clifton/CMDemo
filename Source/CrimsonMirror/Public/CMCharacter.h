#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CMCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UAbilitySystemComponent;

UCLASS()
class CRIMSONMIRROR_API ACMCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACMCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem;

	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMoving();

	virtual void Tick(float DeltaTime) override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };
};
