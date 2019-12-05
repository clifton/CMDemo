#pragma once

#include "CoreMinimal.h"
#include "CMCharacter.h"
#include "CMPlayerCharacter.generated.h"


UENUM(BlueprintType)
enum class EAbilityMap : uint8
{
	PrimaryAttack,
	EAbilityMap_MAX
};

UCLASS()
class CRIMSONMIRROR_API ACMPlayerCharacter : public ACMCharacter
{
	GENERATED_BODY()
	
public:
	ACMPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	// handle input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Velocity);
	void MoveRight(float Velocity);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
	void BeginAbility(EAbilityMap AbilityType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
	void EndAbility(EAbilityMap AbilityType);

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector CharacterAcceleration;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FRotator CharacterAimRotation;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FRotator GetDesiredRotation();
};
