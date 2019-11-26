#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
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

	ECMMovementDirection GetMovementDirection();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlendMode")
	ECMMovementDirection MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FRotator RelativeRotation;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void GetMovementDirections(ECMMovementDirection& Primary, ECMMovementDirection& Secondary);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	static FVector RelativeVelocityNormalized(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	static float ForwardToLateralVelocityRelativeWeight(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetRelativeYawFromDirection(ECMMovementDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetStartTimeFromDistanceCurve(UAnimSequence* Sequence);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector ExpectedStopLocation();

	virtual void Tick(float DeltaTime) override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystem; };
};
