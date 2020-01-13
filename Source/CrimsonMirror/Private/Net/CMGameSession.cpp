#include "Net/CMGameSession.h"
#include "Online.h"
#include "OnlineSubsystemSessionSettings.h"
#include "CMGameModeBase.h"


void ACMGameSession::RegisterServer()
{
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
		if (Sessions.IsValid())
		{
			ACMGameModeBase* MyGM = Cast<ACMGameModeBase>(GetWorld()->GetAuthGameMode());
			if (MyGM)
			{
				TSharedPtr<FOnlineSessionSettings> HostSettings = MakeShareable(new FOnlineSessionSettings());
				// false, false, MaxPlayers

				HostSettings->Set(SETTING_GAMEMODE, FString(*MyGM->GetName()), EOnlineDataAdvertisementType::ViaOnlineService);
				HostSettings->Set(SETTING_MAPNAME, GetWorld()->GetMapName(), EOnlineDataAdvertisementType::ViaOnlineService);
				HostSettings->Set(SETTING_MATCHING_HOPPER, FString("Deathmatch"), EOnlineDataAdvertisementType::DontAdvertise);
				HostSettings->Set(SETTING_MATCHING_TIMEOUT, 120.0f, EOnlineDataAdvertisementType::ViaOnlineService);
				HostSettings->Set(SETTING_SESSION_TEMPLATE_NAME, FString("GameSession"), EOnlineDataAdvertisementType::DontAdvertise);
				HostSettings->bUsesPresence = false;
				HostSettings->bIsLANMatch = false;
				HostSettings->bIsDedicated = true;
				HostSettings->bShouldAdvertise = true;
				// HostSettings->bAllowJoinInProgress = MyGM->bAllowJoinInProgress;
				HostSettings->NumPublicConnections = MaxPlayers;
				Sessions->CreateSession(0, GameSessionName, *HostSettings);
			}
		}
	}
}
