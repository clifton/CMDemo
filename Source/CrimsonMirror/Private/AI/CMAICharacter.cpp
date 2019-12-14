#include "AI/CMAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/CMCharacterStatusBarWidget.h"


ACMAICharacter::ACMAICharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create ability system component, and set it to be explicitly replicated
	HardRefAbilitySystemComponent = CreateDefaultSubobject<UCMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HardRefAbilitySystemComponent->SetIsReplicated(true);

	// Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	HardRefAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// Set our parent's TWeakObjectPtr
	AbilitySystemComponent = HardRefAbilitySystemComponent;

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	HardRefCharacterAttributeSet = CreateDefaultSubobject<UCMCharacterAttributeSet>(TEXT("CharacterAttributeSet"));

	// Set our parent's TWeakObjectPtr
	CharacterAttributeSet = HardRefCharacterAttributeSet;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_DAMAGE, ECollisionResponse::ECR_Block);

	RootComponent = GetCapsuleComponent();

	// create weapon component
	UIStatusBarComp = CreateDefaultSubobject<UWidgetComponent>(FName("UIStatusBarComponent"));
	UIStatusBarComp->SetupAttachment(RootComponent);
	UIStatusBarComp->SetRelativeLocation(FVector(0, 0, 1.1f * GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	UIStatusBarComp->SetWidgetSpace(EWidgetSpace::Screen);
	UIStatusBarComp->SetDrawSize(FVector2D(500, 500));
}

void ACMAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!AbilitySystemComponent.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Ability System Component on %s"), *GetName());
	}
	else
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();
		AddStartupEffects();
		AddCharacterAbilities();

		// Setup FloatingStatusBar UI for Locally Owned Players only, not AI or the server's copy of the PlayerControllers
		InitializeUIStatusBar();

		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetHealthAttribute()).AddUObject(this, &ACMAICharacter::HealthChanged);

		// Tag change callbacks
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(GAMEPLAYTAG_LOSS_OF_CONTROL), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACMAICharacter::LoseControlTagChanged);
	}
}

void ACMAICharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update floating status bar
	UCMCharacterStatusBarWidget* PlayerFloatingStatusBar = GetUIStatusBar();
	if (PlayerFloatingStatusBar)
	{
		PlayerFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
	}

	// If the minion died, handle death
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		Die();
	}
}

void ACMAICharacter::LoseControlTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName(GAMEPLAYTAG_NOTCANCELEDBYLOSSOFCONTROL)));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
