#include "Net/CMSteamCallProxyBase.h"
#include "Net/CMNetTypes.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"


UCMSteamCallProxyBase::UCMSteamCallProxyBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, OnReadFriendsListCompleteDelegate(FOnReadFriendsListComplete::CreateUObject(this, &UCMSteamCallProxyBase::OnGetSteamFriendsComplete))

{

}

void UCMSteamCallProxyBase::Activate()
{
	if (PlayerControllerWeakPtr.IsValid())
	{
		IOnlineFriendsPtr FriendsInterface = Online::GetFriendsInterface();
		if (FriendsInterface.IsValid())
		{
			// const ULocalPlayer* LocalPlayer = PlayerControllerWeakPtr->GetLocalPlayer();
			// FriendsInterface->ReadFriendsList(LocalPlayer->GetControllerId(), EFriendsLists::ToString(EFriendsLists::Default), OnReadFriendsListCompleteDelegate);
			return;
		}
	}
	TArray<FCMSteamFriend> SteamFriends;
	OnFailure.Broadcast(SteamFriends);
}

void UCMSteamCallProxyBase::OnGetSteamFriendsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr)
{
	TArray<FCMSteamFriend> SteamFriends;
	if (bWasSuccessful)
	{
		IOnlineFriendsPtr FriendsInterface = Online::GetFriendsInterface();
		if (FriendsInterface.IsValid())
		{
			TArray<TSharedRef<FOnlineFriend>> FriendsList;
			FriendsInterface->GetFriendsList(LocalUserNum, ListName, FriendsList);

			for (TSharedRef<FOnlineFriend> Friend : FriendsList)
			{
				// Get Presence State
				FOnlineUserPresence Presence = Friend->GetPresence();

				// Dummy Array Entry
				FCMSteamFriend SteamFriend;

				SteamFriend.DisplayName = Friend->GetDisplayName();
				SteamFriend.RealName = Friend->GetRealName();
				SteamFriend.StatusString = Presence.Status.StatusStr;
				SteamFriend.bIsOnline = Presence.bIsOnline;
				SteamFriend.bIsPlaying = Presence.bIsPlaying;
				SteamFriend.bIsPlayingSameGame = Presence.bIsPlayingThisGame;
				SteamFriend.bIsJoinable = Presence.bIsJoinable;
				SteamFriend.bHasVoiceSupport = Presence.bHasVoiceSupport;
				SteamFriend.PresenceState = (EOnlinePresenceState::Type)(int32)Presence.Status.State;
				SteamFriend.UniqueNetID = Friend->GetUserId();

				SteamFriends.Add(SteamFriend);
			}

			OnSuccess.Broadcast(SteamFriends);
			return;
		}
	}
	OnFailure.Broadcast(SteamFriends);
}

UCMSteamCallProxyBase* UCMSteamCallProxyBase::GetSteamFriends(UObject* InWorldContextObject, class APlayerController* InPlayerController)
{
	// Create a new Proxy and fill in the passed variables.
	UCMSteamCallProxyBase* Proxy = NewObject<UCMSteamCallProxyBase>();
	Proxy->WorldContextObject = InWorldContextObject;
	Proxy->PlayerControllerWeakPtr = MakeWeakObjectPtr<APlayerController>(InPlayerController);
	return Proxy;
}
