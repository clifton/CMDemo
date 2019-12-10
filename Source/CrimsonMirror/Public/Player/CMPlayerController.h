#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CMCharacter.h"
#include "CMFloatingCombatTextComponent.h"
#include "CMPlayerController.generated.h"


UCLASS()
class CRIMSONMIRROR_API ACMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void CreateHUD();

	UPROPERTY(EditAnywhere, Category = "CrimsonMirror|UI")
	TSubclassOf<UCMFloatingCombatTextComponent> DamageNumberClass;

	class UCMHUDWidget* GetHUD();

	UFUNCTION(Client, Reliable, WithValidation)
	void ShowDamageNumber(float DamageAmount, ACMCharacter* TargetCharacter);
	void ShowDamageNumber_Implementation(float DamageAmount, ACMCharacter* TargetCharacter);
	bool ShowDamageNumber_Validate(float DamageAmount, ACMCharacter* TargetCharacter);

	// Simple way to RPC to the client the countdown until they respawn from the GameMode. Will be latency amount of out sync with the Server.
	UFUNCTION(Client, Reliable, WithValidation)
	void SetRespawnCountdown(float RespawnTimeRemaining);
	void SetRespawnCountdown_Implementation(float RespawnTimeRemaining);
	bool SetRespawnCountdown_Validate(float RespawnTimeRemaining);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrimsonMirror|UI")
	TSubclassOf<class UCMHUDWidget> UIHUDWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrimsonMirror|UI")
	class UCMHUDWidget* UIHUDWidget;

	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;
};
