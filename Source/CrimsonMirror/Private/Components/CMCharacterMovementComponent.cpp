#include "Components/CMCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "CMCharacter.h"
#include "CrimsonMirror.h"


// base functionality lifted from https://github.com/tranek/GASDocumentation/blob/master/Source/GASDocumentation/Private/Characters/GDCharacterMovementComponent.cpp
UCMCharacterMovementComponent::UCMCharacterMovementComponent()
{
	SprintSpeedMultiplier = 1.4f;
	WalkSpeedMultiplier = 0.5f;
}

float UCMCharacterMovementComponent::GetMaxSpeed() const
{
	ACMCharacter* Owner = Cast<ACMCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), TEXT(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}

	// stunned, disoriented, incapacitated, being knocked back
	if (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.CC.LossOfControl"))))
	{
		return 0.0f;
	}

	// handle roots and snares here

	if (RequestToStartSprinting)
	{
		return Owner->GetMoveSpeed() * SprintSpeedMultiplier;
	}

	if (RequestToStartWalking)
	{
		return Owner->GetMoveSpeed() * WalkSpeedMultiplier;
	}

	return Owner->GetMoveSpeed();
}

void UCMCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	//The Flags parameter contains the compressed input flags that are stored in the saved move.
	//UpdateFromCompressed flags simply copies the flags from the saved move into the movement component.
	//It basically just resets the movement component to the state when the move was made so it can simulate from there.
	RequestToStartSprinting = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;

	RequestToStartWalking = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
}

FNetworkPredictionData_Client* UCMCharacterMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != NULL);

	if (!ClientPredictionData)
	{
		UCMCharacterMovementComponent* MutableThis = const_cast<UCMCharacterMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FCMNetworkPredictionData_Client(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void UCMCharacterMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void UCMCharacterMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}

void UCMCharacterMovementComponent::StartWalking()
{
	RequestToStartWalking = true;
}

void UCMCharacterMovementComponent::StopWalking()
{
	RequestToStartWalking = false;
}

void UCMCharacterMovementComponent::FCMSavedMove::Clear()
{
	Super::Clear();

	SavedRequestToStartSprinting = false;
	SavedRequestToStartWalking = false;
}

uint8 UCMCharacterMovementComponent::FCMSavedMove::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (SavedRequestToStartSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	if (SavedRequestToStartWalking)
	{
		Result |= FLAG_Custom_1;
	}

	return Result;
}

bool UCMCharacterMovementComponent::FCMSavedMove::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
	//Set which moves can be combined together. This will depend on the bit flags that are used.
	if (SavedRequestToStartSprinting != ((FCMSavedMove*)&NewMove)->SavedRequestToStartSprinting)
	{
		return false;
	}

	if (SavedRequestToStartWalking != ((FCMSavedMove*)&NewMove)->SavedRequestToStartWalking)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void UCMCharacterMovementComponent::FCMSavedMove::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	UCMCharacterMovementComponent* CharacterMovement = Cast<UCMCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		SavedRequestToStartSprinting = CharacterMovement->RequestToStartSprinting;
		SavedRequestToStartWalking = CharacterMovement->RequestToStartWalking;
	}
}

void UCMCharacterMovementComponent::FCMSavedMove::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	UCMCharacterMovementComponent* CharacterMovement = Cast<UCMCharacterMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
	}
}

UCMCharacterMovementComponent::FCMNetworkPredictionData_Client::FCMNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr UCMCharacterMovementComponent::FCMNetworkPredictionData_Client::AllocateNewMove()
{
	return FSavedMovePtr(new FCMSavedMove());
}
