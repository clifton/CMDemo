#include "CMGameplayAbility.h"
#include "GameplayTagContainer.h"
#include "CMGEGlobalCooldown.h"
#include "CMAbilitySystemComponent.h"


UCMGameplayAbility::UCMGameplayAbility()
{
	// Default to Instance Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// Default tags that block this ability from activating
	ActivationBlockedTags.AddTag(TagFor(GAMEPLAYTAG_DEAD));
	// stunned, disoriented, incapacitated, being knocked back
	ActivationBlockedTags.AddTag(TagFor(GAMEPLAYTAG_LOSS_OF_CONTROL));

	GlobalCooldownEffectClass = UCMGEGlobalCooldown::StaticClass();
}

void UCMGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

bool UCMGameplayAbility::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /*= nullptr*/,
	const FGameplayTagContainer* TargetTags /*= nullptr*/, OUT FGameplayTagContainer* OptionalRelevantTags /*= nullptr*/) const
{
	// immediately return false if failed in parent check
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;

	// if ability does not bypass gcd and character is currently on gcd
	if (!bDoesBypassGlobalCooldown() && GCDTimeRemaining(ActorInfo) > 0.f) return false;

	return true;
}

void UCMGameplayAbility::PreActivate(
	const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate);

	// apply global cooldown effect
	if (!bDoesBypassGlobalCooldown())
	{
		UGameplayEffect* GCDEffect = GlobalCooldownEffectClass->GetDefaultObject<UGameplayEffect>();
		ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GCDEffect, GetAbilityLevel(Handle, ActorInfo));
	}
}

float UCMGameplayAbility::GetCooldownTimeRemaining(const FGameplayAbilityActorInfo* ActorInfo) const
{
	const float CooldownTimeRemaining = Super::GetCooldownTimeRemaining(ActorInfo);
	if (CooldownTimeRemaining > CM_TIMING_GLOBALCOOLDOWN) return CooldownTimeRemaining;
	
	return FMath::Max(CooldownTimeRemaining, GCDTimeRemaining(ActorInfo));
}

// just for typing less
const FGameplayTag UCMGameplayAbility::TagFor(const FName& TagName)
{
	return FGameplayTag::RequestGameplayTag(TagName);
}

const bool UCMGameplayAbility::bDoesBypassGlobalCooldown() const
{
	// if the ability isnt a character skill or if it is a character skill and bypasses global cooldown
	return !AbilityTags.HasTag(TagFor(GAMEPLAYTAG_CHARACTERSKILL)) || AbilityTags.HasTag(TagFor(GAMEPLAYTAG_NOTBLOCKEDBYGCD));
}

const float UCMGameplayAbility::GCDTimeRemaining(const FGameplayAbilityActorInfo* ActorInfo) const
{
	UCMAbilitySystemComponent* ASC = Cast<UCMAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	if (ASC)
	{
		return ASC->GCDTimeRemaining();
	}
	return 0.f;
}
