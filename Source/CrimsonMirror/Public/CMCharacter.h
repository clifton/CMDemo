#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/CMCharacterAttributeSet.h"
#include "Abilities/CMGameplayAbility.h"
#include "Abilities/CMAbilitySystemComponent.h"
#include "Interfaces/CMTargetableInterface.h"
#include "CrimsonMirror.h"
#include "CMCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterBaseHitReactDelegate, ECMHitReactDirection, Direction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACMCharacter*, Character);

UCLASS()
class CRIMSONMIRROR_API ACMCharacter : public ACharacter, public IAbilitySystemInterface, public ICMTargetableInterface
{
	GENERATED_BODY()

public:
	static int32 DebugMovement;
	static int32 DebugAttacks;

	// BEGIN template functions

	// Sets default values for this character's properties
	ACMCharacter(const class FObjectInitializer& ObjectInitializer);

	// Set the Hit React direction in the Animation Blueprint
	UPROPERTY(BlueprintAssignable, Category = "CMCharacter")
	FCharacterBaseHitReactDelegate ShowHitReact;

	UPROPERTY(BlueprintAssignable, Category = "CMCharacter")
	FCharacterDiedDelegate OnCharacterDied;

	UPROPERTY(Replicated, BlueprintReadWrite, VisibleAnywhere, Category = "Target System")
	AActor* CurrentTarget;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrimsonMirror|UI")
	TSubclassOf<class UCMCharacterStatusBarWidget> UICharacterStatusBarClass;

	UPROPERTY()
	class UCMCharacterStatusBarWidget* UIStatusBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "CrimsonMirror|UI")
	class UWidgetComponent* UIStatusBarComp;

	UFUNCTION(BlueprintCallable, Category = "CMCharacter")
	virtual bool IsAlive() const;

	// Switch on AbilityID to return individual ability levels. Hardcoded to 1 for every ability in this project.
	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDCharacter")
	virtual int32 GetAbilityLevel(ECMAbilityInputID AbilityID) const;

	// Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	virtual void RemoveCharacterAbilities();

	UFUNCTION(BlueprintCallable)
	ECMHitReactDirection GetHitReactDirection(const FVector& ImpactPoint);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	virtual void PlayHitReact(FGameplayTag HitDirection, AActor* DamageCauser);
	virtual void PlayHitReact_Implementation(FGameplayTag HitDirection, AActor* DamageCauser);
	virtual bool PlayHitReact_Validate(FGameplayTag HitDirection, AActor* DamageCauser);

	/**
	* Getters for attributes from CMCharacterAttributeSet
	**/

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetMaxStamina() const;

	// Gets the Current value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetMoveSpeed() const;

	// Gets the Base value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	float GetMoveSpeedBaseValue() const;

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	int32 GetCharacterLevel() const;

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "CMCharacter|Attributes")
	virtual void FinishDying();

	// END template functions

	UFUNCTION(BlueprintCallable)
	bool IsDebugMovementEnabled() { return DebugMovement > 0; };
	UFUNCTION(BlueprintCallable)
	bool IsDebugAttacksEnabled() { return DebugAttacks > 0; };

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void OnTakeDamage(ACMCharacter* WhoAttackedMe, float DamageAmount, bool IsCritical);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void OnInflictDamage(ACMCharacter* WhoWasDamaged, float DamageAmount, bool IsCritical);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void CalculateUpdatedDamage(float OriginalDamage, const UCMCharacterAttributeSet* SourceAttributes, FGameplayTagContainer EffectTags, float& NewDamage, bool& IsCritical);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat")
	void OnDeath(ACMCharacter* WhoKilledMe);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FRotator GetRelativeRotation();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	ECMMovementDirection GetMovementDirection();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetFloorSlope();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void GetMovementDirections(ECMMovementDirection& Primary, ECMMovementDirection& Secondary);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector RelativeVelocityNormalized();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float ForwardToLateralVelocityRelativeWeight();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetRelativeYawFromDirection(ECMMovementDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetStartTimeFromDistanceCurve(UAnimSequence* Sequence);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector ExpectedStopLocation();

	class UCMCharacterStatusBarWidget* GetUIStatusBar();

	virtual void Tick(float DeltaTime) override;

	// implement ICMTargetableInterface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetSystem")
	bool IsTargetable() const;
	virtual bool IsTargetable_Implementation() const override;

	// implement ICMTargetableInterface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetSystem")
	void OnTargeted() const;
	virtual void OnTargeted_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetSystem")
	void OnUntargeted() const;
	virtual void OnUntargeted_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Traces")
	TArray<FHitResult> MeleeHitTrace(float AngleFromFront = 90.f, float MaxHitDistance = -1.f);

	UFUNCTION(Server, Reliable)
	void SetCurrentTarget(AActor* NewTarget);

protected:
	virtual void BeginPlay() override;


	// Creates and initializes the floating status bar for heroes.
	// Safe to call many times because it checks to make sure it only executes once.
	UFUNCTION()
	void InitializeUIStatusBar();

	// BEGIN template functions/attributes


	// Instead of TWeakObjectPtrs, you could just have UPROPERTY() hard references or no references at all and just call
	// GetAbilitySystem() and make a GetAttributeSet() that can read from the PlayerState or from child classes.
	// Just make sure you test if the pointer is valid before using.
	// I opted for TWeakObjectPtrs because I didn't want a shared hard reference here and I didn't want an extra function call of getting
	// the ASC/AttributeSet from the PlayerState or child classes every time I referenced them in this base class.

	TWeakObjectPtr<class UCMAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCMCharacterAttributeSet> CharacterAttributeSet;

	FGameplayTag HitDirectionFrontTag;
	FGameplayTag HitDirectionBackTag;
	FGameplayTag HitDirectionRightTag;
	FGameplayTag HitDirectionLeftTag;
	FGameplayTag DeadTag;
	FGameplayTag EffectNotCanceledOnDeath;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CrimsonMirror|CMCharacter")
	FText CharacterName;

	// Death Animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	UAnimMontage* DeathMontage;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CrimsonMirror|Abilities")
	TArray<TSubclassOf<class UCMGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CrimsonMirror|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CrimsonMirror|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attributes Base Value.
	*/

	virtual void SetHealth(float Health);
	virtual void SetMana(float Mana);
	virtual void SetStamina(float Stamina);

	// END template functions/attributes

private:
	FVector GetVelocity() const override { return Super::GetVelocity(); };
};
