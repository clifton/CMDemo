#include "CMAbilityTask_WaitForOverlap.h"


UCMAbilityTask_WaitForOverlap::UCMAbilityTask_WaitForOverlap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UCMAbilityTask_WaitForOverlap* UCMAbilityTask_WaitForOverlap::CMWaitForOverlap(
	UGameplayAbility* OwningAbility, TArray<UPrimitiveComponent*> CollisionPrimitives, bool bOnlyUniqueHits /*= true*/)
{
	// auto MyObj = NewAbilityTask<UCMAbilityTask_WaitForOverlap>(OwningAbility);
	// MyObj->CollisionPrimitive = WeaponCollisionPrimitive;
	UCMAbilityTask_WaitForOverlap* MyTask = NewAbilityTask<UCMAbilityTask_WaitForOverlap>(OwningAbility);
	MyTask->bOnlyUniqueHits = bOnlyUniqueHits;
	MyTask->CollisionPrimitives = CollisionPrimitives;
	return MyTask;
}

void UCMAbilityTask_WaitForOverlap::Activate()
{
	SetWaitingOnAvatar();

	for (UPrimitiveComponent* CollisionComp : CollisionPrimitives)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit! %s"), *CollisionComp->GetName());
	}
}

void UCMAbilityTask_WaitForOverlap::OnOverlapCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void UCMAbilityTask_WaitForOverlap::OnDestroy(bool AbilityEnded)
{

}
