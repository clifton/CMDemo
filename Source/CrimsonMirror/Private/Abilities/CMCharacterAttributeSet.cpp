#include "CMCharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "CMCharacter.h"
#include "GameplayEffectExtension.h"
#include "GameplayTagsModule.h"
#include "GameplayTagContainer.h"


UCMCharacterAttributeSet::UCMCharacterAttributeSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxHealth = 1000.f;
	Health = MaxHealth;
}

bool UCMCharacterAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	static UProperty* HealthProperty = FindFieldChecked<UProperty>(UCMCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCMCharacterAttributeSet, Health));
	static UProperty* DamageProperty = FindFieldChecked<UProperty>(UCMCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCMCharacterAttributeSet, Damage));
	static UProperty* HealingProperty = FindFieldChecked<UProperty>(UCMCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCMCharacterAttributeSet, Healing));

	UProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();

	if (DamageProperty == ModifiedProperty)
	{
		ACMCharacter* MyCharacter = CastChecked<ACMCharacter>(GetOwningActor());
		float NewMagnitude = Data.EvaluatedData.Magnitude;
		bool IsCritical = false;

		const UCMCharacterAttributeSet* SourceAttributes = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent()->GetSet<UCMCharacterAttributeSet>();

		FGameplayTagContainer EffectTags;
		Data.EffectSpec.GetAllAssetTags(EffectTags);

		MyCharacter->CalculateUpdatedDamage(Data.EvaluatedData.Magnitude, SourceAttributes, EffectTags, NewMagnitude, IsCritical);

		Data.EvaluatedData.Magnitude = NewMagnitude;
		WhoAttackedUsLast = Cast<ACMCharacter>(Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent()->GetOwner());

		if (NewMagnitude > 0.f)
		{
			ACMCharacter* DamagedCharacter = Cast<ACMCharacter>(GetOwningActor());
			if (DamagedCharacter)
			{
				DamagedCharacter->OnTakeDamage(WhoAttackedUsLast, NewMagnitude, IsCritical);

				if (WhoAttackedUsLast)
				{
					ACMCharacter* AttackingCharacter = Cast<ACMCharacter>(WhoAttackedUsLast);

					if (AttackingCharacter)
					{
						AttackingCharacter->OnInflictDamage(DamagedCharacter, NewMagnitude, IsCritical);
					}

					UE_LOG(LogTemp, Warning, TEXT("%s did %s damage to %s"),
						*WhoAttackedUsLast->GetName(), *FString::SanitizeFloat(NewMagnitude), *DamagedCharacter->GetName());
				}
			}
		}
	}

	return true;
}

void UCMCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	static UProperty* DamageProperty = FindFieldChecked<UProperty>(UCMCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCMCharacterAttributeSet, Damage));
	static UProperty* HealingProperty = FindFieldChecked<UProperty>(UCMCharacterAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UCMCharacterAttributeSet, Healing));
	UProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();

	if (DamageProperty == ModifiedProperty)
	{
		SetHealth(FMath::Clamp(GetHealth() - Damage.GetCurrentValue(), 0.f, GetMaxHealth()));
		Damage = 0.f;
	}

	if (HealingProperty == ModifiedProperty)
	{
		SetHealth(FMath::Clamp(GetHealth() + Healing.GetCurrentValue(), 0.f, GetMaxHealth()));
		Healing = 0.f;
	}

	//Dead
	if (GetHealth() <= 0.f)
	{
		FName DeadTagName = FName(TEXT("Combat.State.Dead"));
		FGameplayTag DeadTag = UGameplayTagsManager::Get().RequestGameplayTag(DeadTagName);

		ACMCharacter* MyCharacter = Cast<ACMCharacter>(GetOwningActor());
		if (MyCharacter && !MyCharacter->GetAbilitySystemComponent()->HasAnyMatchingGameplayTags(FGameplayTagContainer(DeadTag)))
		{
			UE_LOG(LogTemp, Warning, TEXT("DEAD!"));
			MyCharacter->OnDeath(WhoAttackedUsLast);
		}
	}
}

void UCMCharacterAttributeSet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCMCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCMCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
}
