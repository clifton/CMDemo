#include "CMAbilitySystemComponent.h"


void UCMAbilitySystemComponent::ReceiveDamage(UCMAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
