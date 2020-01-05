#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "CMNetTypes.generated.h"


/**
*	Struct defining a SteamFriend, which can be accessed in Blueprints.
*/
USTRUCT(BlueprintType)
struct FCMSteamFriend
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	FString RealName;

	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	FString StatusString;

	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	bool bIsOnline;

	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	bool bIsPlaying;

	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	bool bIsPlayingSameGame;

	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	bool bIsJoinable;

	UPROPERTY(BlueprintReadOnly, Category = "Net|Steam|Friends")
	bool bHasVoiceSupport;

	EOnlinePresenceState::Type PresenceState;

	TSharedPtr<const FUniqueNetId> UniqueNetID;
};

/**
*	Enum used for the Execs of the Static Functions.
*/
UENUM()
enum class ECMAsyncResultSwitch : uint8
{
	OnSuccess,
	AsyncLoading,
	OnFailure
};

/**
*	Enum use for requesting a specific Avatar size.
*/
UENUM(Blueprintable)
enum class ECMAvatarSize : uint8
{
	SF_NONE = 0     UMETA(Hidden = true),
	SF_SMALL = 1	UMETA(DisplayName = "Small Avatar"),
	SF_MEDIUM = 2	UMETA(DisplayName = "Medium Avatar"),
	SF_LARGE = 3	UMETA(DisplayName = "Large Avatar")
};