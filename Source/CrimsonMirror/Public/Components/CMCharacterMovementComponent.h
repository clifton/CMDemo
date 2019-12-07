#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CMCharacterMovementComponent.generated.h"


// base functionality lifted from https://github.com/tranek/GASDocumentation/blob/master/Source/GASDocumentation/Public/Characters/GDCharacterMovementComponent.h
UCLASS()
class CRIMSONMIRROR_API UCMCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	class FCMSavedMove : public FSavedMove_Character
	{
	public:

		typedef FSavedMove_Character Super;

		///@brief Resets all saved variables.
		virtual void Clear() override;

		///@brief Store input commands in the compressed flags.
		virtual uint8 GetCompressedFlags() const override;

		///@brief This is used to check whether or not two moves can be combined into one.
		///Basically you just check to make sure that the saved variables are the same.
		virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;

		///@brief Sets up the move before sending it to the server. 
		virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character& ClientData) override;
		///@brief Sets variables on character movement component before making a predictive correction.
		virtual void PrepMoveFor(class ACharacter* Character) override;

		// Sprint
		uint8 SavedRequestToStartSprinting : 1;

		// Walking
		uint8 SavedRequestToStartWalking : 1;
	};

	class FCMNetworkPredictionData_Client : public FNetworkPredictionData_Client_Character
	{
	public:
		FCMNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement);

		typedef FNetworkPredictionData_Client_Character Super;

		///@brief Allocates a new copy of our custom saved move
		virtual FSavedMovePtr AllocateNewMove() override;
	};

public:
	UCMCharacterMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Walking")
	float WalkSpeedMultiplier;

	uint8 RequestToStartSprinting : 1;
	uint8 RequestToStartWalking : 1;

	virtual float GetMaxSpeed() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	virtual class FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	// Sprint
	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StartSprinting();
	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StopSprinting();

	// Aim Down Sights
	UFUNCTION(BlueprintCallable, Category = "Walking")
	void StartWalking();
	UFUNCTION(BlueprintCallable, Category = "Walking")
	void StopWalking();
};
