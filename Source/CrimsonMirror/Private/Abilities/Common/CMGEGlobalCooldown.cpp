#include "Abilities/Common/CMGEGlobalCooldown.h"
#include "CrimsonMirror.h"


UCMGEGlobalCooldown::UCMGEGlobalCooldown()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(1.0f);
	// gameplay tag of the effect itself
	InheritableGameplayEffectTags.AddTag(FGameplayTag::RequestGameplayTag(GAMEPLAYEFFECT_GLOBALCOOLDOWN));
	// gameplay tag given or refreshed on owner
	InheritableOwnedTagsContainer.AddTag(FGameplayTag::RequestGameplayTag(GAMEPLAYTAG_GLOBALCOOLDOWN));
}
