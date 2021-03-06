#pragma once

#include "CoreMinimal.h"
#include "CMCharacter.h"
#include "CMPlayerCharacter.generated.h"


UCLASS()
class CRIMSONMIRROR_API ACMPlayerCharacter : public ACMCharacter
{
	GENERATED_BODY()
	
public:
	ACMPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category = "TargetSystem")
	void GetNewTarget();

	// handle input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class USpringArmComponent* GetCameraBoom();
	class UCameraComponent* GetFollowCamera();

	UFUNCTION(BlueprintCallable, Category = "CrimsonMirror|Camera")
	float GetStartingCameraBoomArmLength();

	UFUNCTION(BlueprintCallable, Category = "CrimsonMirror|Camera")
	FVector GetStartingCameraBoomLocation();

	virtual void FinishDying() override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector CharacterAcceleration;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FRotator CharacterAimRotation;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	const FRotator GetDesiredRotation();

	virtual void Die() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrimsonMirror|Camera")
	float BaseTurnRate = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrimsonMirror|Camera")
	float BaseLookUpRate = 45.0f;

	UPROPERTY(BlueprintReadOnly, Category = "CrimsonMirror|Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly, Category = "CrimsonMirror|Camera")
	FVector StartingCameraBoomLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrimsonMirror|Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrimsonMirror|Camera")
	class UCameraComponent* FollowCamera;

	class UCMTargetSystemComponent* TargetSystem;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	// Mouse
	void LookUp(float Value);

	// Gamepad
	void LookUpRate(float Value);

	// Mouse
	void Turn(float Value);

	// Gamepad
	void TurnRate(float Value);

	// Mouse + Gamepad
	void MoveForward(float Value);

	// Mouse + Gamepad
	void MoveRight(float Value);

	// Client only
	virtual void OnRep_PlayerState() override;

private:
	FTimerHandle TimerHandle_TryInitializeAbilityBinds;
	TWeakObjectPtr<UInputComponent> WeakInputComponent;

	void TryActivateBinds();
};
