#pragma once

#include "CoreMinimal.h"


// Network Defines
#define ACTOR_ROLE_FSTRING				*(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(Role))
#define GET_ACTOR_ROLE_FSTRING(Actor)	*(FindObject<UEnum>(ANY_PACKAGE, TEXT("ENetRole"), true)->GetNameStringByValue(Actor->Role))

// Collision Trace Channels
#define COLLISION_DAMAGE				ECC_GameTraceChannel1

// Surface Types
// flesh, wood, stone, metal, etc

// Gameplay Tags
#define GAMEPLAYTAG_DEAD				FName("State.Dead")
#define GAMEPLAYTAG_LOSS_OF_CONTROL		FName("State.Debuff.CC.LossOfControl")
#define GAMEPLAYTAG_GLOBALCOOLDOWN		FName("State.GCD")
#define GAMEPLAYTAG_NOTBLOCKEDBYGCD		FName("Effect.NotBlockedByGCD")
#define GAMEPLAYTAG_CHARACTERSKILL		FName("Ability.Skill")

// Gameplay effect tags
#define GAMEPLAYEFFECT_GLOBALCOOLDOWN   FName("Effect.GlobalCooldown")

// gameplay constants
#define CM_TIMING_GLOBALCOOLDOWN		1.0f


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
	None			UMETA(DisplayName = "None"),		// 0	None
	Confirm			UMETA(DisplayName = "Confirm"),		// 1	Confirm
	Cancel			UMETA(DisplayName = "Cancel"),		// 2	Cancel
	AbilityLMB		UMETA(DisplayName = "AbilityLMB"),	// 3	LMB
	AbilityRMB		UMETA(DisplayName = "AbilityRMB"),	// 4	RMB
	AbilityQ		UMETA(DisplayName = "AbilityQ"),	// 5	Q
	AbilityE		UMETA(DisplayName = "AbilityE"),	// 6	E
	AbilityF		UMETA(DisplayName = "AbilityF"),	// 7	F
	AbilityR		UMETA(DisplayName = "AbilityR"),	// 8	R
	Ability1		UMETA(DisplayName = "Ability1"),	// 9	1
	Ability2		UMETA(DisplayName = "Ability2"),	// 10	2
	Ability3		UMETA(DisplayName = "Ability3"),	// 11	3
	Ability4		UMETA(DisplayName = "Ability4"),	// 12	4
	Ability5		UMETA(DisplayName = "Ability5"),	// 13	5
	Ability6		UMETA(DisplayName = "Ability6"),	// 14	6
	Ability7		UMETA(DisplayName = "Ability7"),	// 15	7
	Ability8		UMETA(DisplayName = "Ability8"),	// 16	8
	Ability9		UMETA(DisplayName = "Ability9"),	// 17	9
	Ability0		UMETA(DisplayName = "Ability0"),	// 18	0
	Sprint			UMETA(DisplayName = "Sprint"),		// 19	Sprint
	Jump			UMETA(DisplayName = "Jump")			// 20	Jump
};

UENUM(BlueprintType)
enum class ECMMovementDirection : uint8
{
	Forward			UMETA(DisplayName = "Forward"),		// 0
	Backward		UMETA(DisplayName = "Backward"),	// 1
	Left			UMETA(DisplayName = "Left"),		// 2
	Right			UMETA(DisplayName = "Right"),		// 3
};
