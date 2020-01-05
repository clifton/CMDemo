#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Net/CMNetTypes.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "CMSteamCallProxyBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCMGetSteamFriendsDelegate, const TArray<FCMSteamFriend>&, Results);

UCLASS()
class CRIMSONMIRROR_API UCMSteamCallProxyBase : public UOnlineBlueprintCallProxyBase
{
	GENERATED_UCLASS_BODY()

private:
	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;
	UObject* WorldContextObject;
	FOnReadFriendsListComplete OnReadFriendsListCompleteDelegate;

public:
	UPROPERTY(BlueprintAssignable)
	FCMGetSteamFriendsDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCMGetSteamFriendsDelegate OnFailure;

	// UOnlineBlueprintCallProxyBase Interface
	virtual void Activate() override;

	// Internal Callback when Friend List Request Completes
	void OnGetSteamFriendsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);

	/**
	*	Static function, used internally to create the Proxy and fill in the needed variables.
	*
	*	@param		InWorldContextObject		World Context Object, in case we need the World.
	*	@param		InPlayerController			PlayerController, which tries to get Steam Friends.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"), Category = "Steam|Friends")
	static UCMSteamCallProxyBase* GetSteamFriends(UObject* InWorldContextObject, class APlayerController* InPlayerController);

};
