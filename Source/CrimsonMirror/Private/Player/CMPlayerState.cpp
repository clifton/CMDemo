#include "CMPlayerState.h"
#include "Abilities/CMCharacterAttributeSet.h"
#include "Abilities/CMAbilitySystemComponent.h"
#include "CMPlayerCharacter.h"
#include "CMPlayerController.h"
#include "UI/CMHUDWidget.h"
#include "UI/CMPlayerStatusBarWidget.h"
// #include "UI/CMFloatingCombatText.h"


ACMPlayerState::ACMPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UCMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	CharacterAttributeSet = CreateDefaultSubobject<UCMCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;

	// Cache tags
	DeadTag = FGameplayTag::RequestGameplayTag(GAMEPLAYTAG_DEAD);
}

UAbilitySystemComponent* ACMPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCMCharacterAttributeSet* ACMPlayerState::GetCharacterAttributeSet() const
{
	return CharacterAttributeSet;
}

bool ACMPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void ACMPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->ShowAbilityConfirmCancelText(ShowText);
		}
	}
}

float ACMPlayerState::GetHealth() const
{
	return CharacterAttributeSet->GetHealth();
}

float ACMPlayerState::GetMaxHealth() const
{
	return CharacterAttributeSet->GetMaxHealth();
}

float ACMPlayerState::GetHealthRegenRate() const
{
	return CharacterAttributeSet->GetHealthRegenRate();
}

float ACMPlayerState::GetMana() const
{
	return CharacterAttributeSet->GetMana();
}

float ACMPlayerState::GetMaxMana() const
{
	return CharacterAttributeSet->GetMaxMana();
}

float ACMPlayerState::GetManaRegenRate() const
{
	return CharacterAttributeSet->GetManaRegenRate();
}

float ACMPlayerState::GetStamina() const
{
	return CharacterAttributeSet->GetStamina();
}

float ACMPlayerState::GetMaxStamina() const
{
	return CharacterAttributeSet->GetMaxStamina();
}

float ACMPlayerState::GetStaminaRegenRate() const
{
	return CharacterAttributeSet->GetStaminaRegenRate();
}

float ACMPlayerState::GetMoveSpeed() const
{
	return CharacterAttributeSet->GetMoveSpeed();
}

void ACMPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetHealthAttribute()).AddUObject(this, &ACMPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ACMPlayerState::MaxHealthChanged);
		HealthRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetHealthRegenRateAttribute()).AddUObject(this, &ACMPlayerState::HealthRegenRateChanged);
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetManaAttribute()).AddUObject(this, &ACMPlayerState::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetMaxManaAttribute()).AddUObject(this, &ACMPlayerState::MaxManaChanged);
		ManaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetManaRegenRateAttribute()).AddUObject(this, &ACMPlayerState::ManaRegenRateChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetStaminaAttribute()).AddUObject(this, &ACMPlayerState::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &ACMPlayerState::MaxStaminaChanged);
		StaminaRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetStaminaRegenRateAttribute()).AddUObject(this, &ACMPlayerState::StaminaRegenRateChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(GAMEPLAYTAG_LOSS_OF_CONTROL), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACMPlayerState::LossOfControlStatusChanged);
	}
}

void ACMPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update floating status bar
	ACMPlayerCharacter* PlayerCharacter = Cast<ACMPlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		UCMPlayerStatusBarWidget* PlayerFloatingStatusBar = PlayerCharacter->GetPlayerStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
		}
	}

	// Update the HUD
	// Handled in the UI itself using the AsyncTaskAttributeChanged node as an example how to do it in Blueprint
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetCurrentHealth(Health);
			HUD->SetHealthPercentage(Health / GetMaxHealth());
		}
	}

	// If the player died, handle death
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		if (PlayerCharacter)
		{
			PlayerCharacter->Die();
		}
	}
}

void ACMPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;

	// Update floating status bar
	ACMPlayerCharacter* PlayerCharacter = Cast<ACMPlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		UCMPlayerStatusBarWidget* PlayerFloatingStatusBar = PlayerCharacter->GetPlayerStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetHealthPercentage(GetHealth() / MaxHealth);
		}
	}

	// Update the HUD
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxHealth(MaxHealth);
			HUD->SetHealthPercentage(GetHealth() / MaxHealth);
		}
	}
}

void ACMPlayerState::HealthRegenRateChanged(const FOnAttributeChangeData& Data)
{
	float HealthRegenRate = Data.NewValue;

	// Update the HUD
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetHealthRegenRate(HealthRegenRate);
		}
	}
}

void ACMPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	float Mana = Data.NewValue;

	// Update floating status bar
	ACMPlayerCharacter* PlayerCharacter = Cast<ACMPlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		UCMPlayerStatusBarWidget* PlayerFloatingStatusBar = PlayerCharacter->GetPlayerStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetManaPercentage(Mana / GetMaxMana());
		}
	}

	// Update the HUD
	// Handled in the UI itself using the AsyncTaskAttributeChanged node as an example how to do it in Blueprint
}

void ACMPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	float MaxMana = Data.NewValue;

	// Update floating status bar
	ACMPlayerCharacter* PlayerCharacter = Cast<ACMPlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		UCMPlayerStatusBarWidget* PlayerFloatingStatusBar = PlayerCharacter->GetPlayerStatusBar();
		if (PlayerFloatingStatusBar)
		{
			PlayerFloatingStatusBar->SetManaPercentage(GetMana() / MaxMana);
		}
	}

	// Update the HUD
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxMana(MaxMana);
		}
	}
}

void ACMPlayerState::ManaRegenRateChanged(const FOnAttributeChangeData& Data)
{
	float ManaRegenRate = Data.NewValue;

	// Update the HUD
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetManaRegenRate(ManaRegenRate);
		}
	}
}

void ACMPlayerState::StaminaChanged(const FOnAttributeChangeData& Data)
{
	float Stamina = Data.NewValue;

	// Update the HUD
	// Handled in the UI itself using the AsyncTaskAttributeChanged node as an example how to do it in Blueprint
}

void ACMPlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	float MaxStamina = Data.NewValue;

	// Update the HUD
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxStamina(MaxStamina);
		}
	}
}

void ACMPlayerState::StaminaRegenRateChanged(const FOnAttributeChangeData& Data)
{
	float StaminaRegenRate = Data.NewValue;

	// Update the HUD
	ACMPlayerController* PC = Cast<ACMPlayerController>(GetOwner());
	if (PC)
	{
		UCMHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetStaminaRegenRate(StaminaRegenRate);
		}
	}
}

void ACMPlayerState::LossOfControlStatusChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByLossOfControl")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
