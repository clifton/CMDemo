#pragma once

#include "CoreMinimal.h"


// Network Defines
#define ACTOR_ROLE_FSTRING *(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(Role))
#define GET_ACTOR_ROLE_FSTRING(Actor) *(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(Actor->Role))


// Collision Trace Channels
#define COLLISION_DAMAGE		ECC_GameTraceChannel1


// Enums
UENUM(BlueprintType)
enum class ECMHitReactDirection : uint8
{
	
	None			UMETA(DisplayName = "None"),		// 0
	Left 			UMETA(DisplayName = "Left"),		// 1
	Front 			UMETA(DisplayName = "Front"),		// 2
	Right			UMETA(DisplayName = "Right"),		// 3
	Back			UMETA(DisplayName = "Back")			// 4
};

UENUM(BlueprintType)
enum class ECMAbilityInputID : uint8
{
	None			UMETA(DisplayName = "None"),		// 0 None
	Confirm			UMETA(DisplayName = "Confirm"),		// 1 Confirm
	Cancel			UMETA(DisplayName = "Cancel"),		// 2 Cancel
	Ability1		UMETA(DisplayName = "Ability1"),	// 3 LMB
	Ability2		UMETA(DisplayName = "Ability2"),	// 4 RMB
	Ability3		UMETA(DisplayName = "Ability3"),	// 5 Q
	Ability4		UMETA(DisplayName = "Ability4"),	// 6 E
	Ability5		UMETA(DisplayName = "Ability5"),	// 7 R
	Sprint			UMETA(DisplayName = "Sprint"),		// 8 Sprint
	Jump			UMETA(DisplayName = "Jump")			// 9 Jump
};

UENUM(BlueprintType)
enum class ECMMovementDirection : uint8
{
	Forward			UMETA(DisplayName = "Forward"),		// 0
	Backward		UMETA(DisplayName = "Backward"),	// 1
	Left			UMETA(DisplayName = "Left"),		// 2
	Right			UMETA(DisplayName = "Right"),		// 3
};