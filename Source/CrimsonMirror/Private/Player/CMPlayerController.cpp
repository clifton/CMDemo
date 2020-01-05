#include "Player/CMPlayerController.h"
#include "Player/CMPlayerState.h"
#include "CMCharacter.h"
#include "UI/CMHUDWidget.h"
#include "UI/CMFloatingCombatTextComponent.h"


void ACMPlayerController::CreateHUD()
{
	// Only create once
	if (UIHUDWidget)
	{
		return;
	}

	if (!UIHUDWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing UIHUDWidgetClass. Please fill in on the Blueprint of the PlayerController."));
		return;
	}

	// Only create a HUD for local player
	if (!IsLocalPlayerController())
	{
		return;
	}

	// Need a valid PlayerState to get attributes from
	ACMPlayerState* PS = GetPlayerState<ACMPlayerState>();
	if (!PS)
	{
		return;
	}

	UIHUDWidget = CreateWidget<UCMHUDWidget>(this, UIHUDWidgetClass);
	UIHUDWidget->AddToViewport();

	// Set attributes
	UIHUDWidget->SetCurrentHealth(PS->GetHealth());
	UIHUDWidget->SetMaxHealth(PS->GetMaxHealth());
	UIHUDWidget->SetHealthPercentage(PS->GetHealth() / PS->GetMaxHealth());
	UIHUDWidget->SetCurrentMana(PS->GetMana());
	UIHUDWidget->SetMaxMana(PS->GetMaxMana());
	UIHUDWidget->SetManaPercentage(PS->GetMana() / PS->GetMaxMana());
	UIHUDWidget->SetHealthRegenRate(PS->GetHealthRegenRate());
	UIHUDWidget->SetManaRegenRate(PS->GetManaRegenRate());
	UIHUDWidget->SetCurrentStamina(PS->GetStamina());
	UIHUDWidget->SetMaxStamina(PS->GetMaxStamina());
	UIHUDWidget->SetStaminaPercentage(PS->GetStamina() / PS->GetMaxStamina());
	UIHUDWidget->SetStaminaRegenRate(PS->GetStaminaRegenRate());
	
	if (!DamageNumberClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find DamageNumberClass. If it was moved, please update the reference location in C++."));
	}
}

UCMHUDWidget* ACMPlayerController::GetHUD()
{
	return UIHUDWidget;
}

void ACMPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACMCharacter* TargetCharacter)
{
	if (TargetCharacter && DamageNumberClass)
	{
		UCMFloatingCombatTextComponent* DamageText = NewObject<UCMFloatingCombatTextComponent>(TargetCharacter, DamageNumberClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}

bool ACMPlayerController::ShowDamageNumber_Validate(float DamageAmount, ACMCharacter* TargetCharacter)
{
	return true;
}

void ACMPlayerController::SetRespawnCountdown_Implementation(float RespawnTimeRemaining)
{
	if (UIHUDWidget)
	{
		UIHUDWidget->SetRespawnCountdown(RespawnTimeRemaining);
	}
}

bool ACMPlayerController::SetRespawnCountdown_Validate(float RespawnTimeRemaining)
{
	return true;
}

// Server only
void ACMPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ACMPlayerState* PS = GetPlayerState<ACMPlayerState>();
	if (PS)
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void ACMPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For edge cases where the PlayerState is repped before the Hero is possessed.
	CreateHUD();
}
