#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMTargetSystemComponent.generated.h"


class ACMPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRIMSONMIRROR_API UCMTargetSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	static int32 DebugTargeting;

	UCMTargetSystemComponent();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Target System")
	AActor* CurrentTarget;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// get a sorted array of actor - score pairs
	TArray<TPair<AActor*, float>> GetTargets();

	// get actor with highest score that hasnt recently been selected
	UFUNCTION(BlueprintCallable)
	void GetTarget();

	// Check to see if target implements ICMTargetableInterface
	UFUNCTION(BlueprintCallable)
	bool TargetIsTargetable(AActor* Actor);
	
	// check if there is a line of sight to the target from the camera or the player pawn not blocked by ECC_WorldStatic
	UFUNCTION(BlueprintCallable)
	bool TargetInLineOfSight(AActor* Actor);

	// check to see if target is in viewport
	UFUNCTION(BlueprintCallable)
	bool TargetIsVisible(AActor* Actor);

	virtual void InitializeComponent() override;

protected:
	TArray<AActor*> AllTargets;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	ACMPlayerCharacter* GetPlayer();
};
