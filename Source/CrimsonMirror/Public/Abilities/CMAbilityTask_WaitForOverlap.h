#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "CMAbilityTask_WaitForOverlap.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitOverlapDelegate, const FGameplayAbilityTargetDataHandle&, TargetData);

class AActor;
class UPrimitiveComponent;

UCLASS()
class UCMAbilityTask_WaitForOverlap : public UAbilityTask
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWaitOverlapDelegate OnOverlap;

	UFUNCTION()
	void OnOverlapCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UCMAbilityTask_WaitForOverlap* CMWaitForOverlap(UGameplayAbility* OwningAbility, TArray<UPrimitiveComponent*> CollisionPrimitives);

private:
	TArray<UPrimitiveComponent*> CollisionPrimitives;

	TSet<AActor*> HitActors;

	virtual void OnDestroy(bool AbilityEnded) override;

	void HandleHit(FHitResult HitResult);
};
