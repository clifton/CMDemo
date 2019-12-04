#include "CMAbilityTask_WaitForOverlap.h"


UCMAbilityTask_WaitForOverlap::UCMAbilityTask_WaitForOverlap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UCMAbilityTask_WaitForOverlap* UCMAbilityTask_WaitForOverlap::CMWaitForOverlap(
	UGameplayAbility* OwningAbility, TArray<UPrimitiveComponent*> CollisionPrimitives)
{
	UCMAbilityTask_WaitForOverlap* MyTask = NewAbilityTask<UCMAbilityTask_WaitForOverlap>(OwningAbility);
	MyTask->CollisionPrimitives = CollisionPrimitives;
	return MyTask;
}

void UCMAbilityTask_WaitForOverlap::Activate()
{
	SetWaitingOnAvatar();

	for (UPrimitiveComponent* CollisionComp : CollisionPrimitives)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
		CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &UCMAbilityTask_WaitForOverlap::OnOverlapCallback);

		TArray<AActor*> OverlappingActors;
		CollisionComp->GetOverlappingActors(OverlappingActors, TSubclassOf<APawn>());
		for (AActor* OverlappingActor : OverlappingActors)
		{
			if (OverlappingActor == GetAvatarActor()) continue;
			
			FHitResult HitResult;
			HitResult.bBlockingHit = true;
			HitResult.Actor = OverlappingActor;
			HitResult.Component = CollisionComp;
			HitResult.Location = CollisionComp->GetComponentLocation();

			HandleHit(HitResult);
			// UE_LOG(LogTemp, Warning, TEXT("Initial hit on %s from %s : %s"), *OverlappingActor->GetName(), *GetAvatarActor()->GetName(), *CollisionComp->GetName());
		}
	}
}

void UCMAbilityTask_WaitForOverlap::HandleHit(FHitResult HitResult)
{
	AActor* OtherActor = HitResult.GetActor();
	if (HitActors.Contains(OtherActor))
	{
		// actor already hit
		return;
	}
	HitActors.Add(HitResult.GetActor());
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
	FGameplayAbilityTargetDataHandle Handle;
	Handle.Data.Add(TSharedPtr<FGameplayAbilityTargetData>(TargetData));
	OnOverlap.Broadcast(Handle);
	// UE_LOG(LogTemp, Warning, TEXT("Hit on %s from %s : %s"), *OtherActor->GetName(), *GetAvatarActor()->GetName(), *HitResult.GetComponent()->GetName());
}

void UCMAbilityTask_WaitForOverlap::OnOverlapCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetAvatarActor() == OtherActor) return;

	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (OtherPawn) HandleHit(SweepResult);
}

void UCMAbilityTask_WaitForOverlap::OnDestroy(bool AbilityEnded)
{
	for (UPrimitiveComponent* CollisionComp : CollisionPrimitives)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionComp->OnComponentBeginOverlap.RemoveDynamic(this, &UCMAbilityTask_WaitForOverlap::OnOverlapCallback);
	}
}
