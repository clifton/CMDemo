#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/CMCharacterAttributeSet.h"
#include "CMCharacter.generated.h"


UENUM(BlueprintType)
enum class ECMMovementDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right,
	Max UMETA(Hidden)
};

class USpringArmComponent;
class UCameraComponent;
class UAbilitySystemComponent;
class UCMCharacterAttributeSet;

UCLASS()
class CRIMSONMIRROR_API ACMCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	static int32 DebugMovement;

	UFUNCTION(BlueprintCallable)
	bool IsDebugMovementEnabled() { return DebugMovement > 0; };

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
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void OnTakeDamage(ACMCharacter* WhoAttackedMe, float DamageAmount, bool IsCritical);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void OnInflictDamage(ACMCharacter* WhoWasDamaged, float DamageAmount, bool IsCritical);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void CalculateUpdatedDamage(float OriginalDamage, const UCMCharacterAttributeSet* SourceAttributes, FGameplayTagContainer EffectTags, float& NewDamage, bool& IsCritical);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void OnDeath(ACMCharacter* WhoKilledMe);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FRotator GetRelativeRotation();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	ECMMovementDirection GetMovementDirection();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetFloorSlope();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void GetMovementDirections(ECMMovementDirection& Primary, ECMMovementDirection& Secondary);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector RelativeVelocityNormalized();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float ForwardToLateralVelocityRelativeWeight();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetRelativeYawFromDirection(ECMMovementDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetStartTimeFromDistanceCurve(UAnimSequence* Sequence);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector ExpectedStopLocation();

	virtual void Tick(float DeltaTime) override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };

private:
	FVector GetVelocity() const override { return Super::GetVelocity(); };
};
