#include "CMAbilitySystemComponent.h"
#include "CrimsonMirror.h"


void UCMAbilitySystemComponent::ReceiveDamage(UCMAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}

const float UCMAbilitySystemComponent::GCDTimeRemaining() const
{
	FGameplayEffectQuery GCDQuery = FGameplayEffectQuery::MakeQuery_MatchAllSourceTags(
		FGameplayTagContainer(FGameplayTag::RequestGameplayTag(GAMEPLAYEFFECT_GLOBALCOOLDOWN)));
	TArray<float> Durations = GetActiveEffectsTimeRemaining(GCDQuery);
	if (Durations.Num() > 0)
	{
		Durations.Sort();
		return Durations[Durations.Num() - 1];
	}
	return 0.f;
}
