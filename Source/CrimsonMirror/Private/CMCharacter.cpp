#include "CMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/CMCharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/CMCharacterStatusBarWidget.h"
#include "Player/CMPlayerController.h"
#include "Animation/AnimSequence.h"
#include "Net/UnrealNetwork.h"
#include "CrimsonMirror.h"


// console variables
int32 ACMCharacter::DebugMovement = 0;
FAutoConsoleVariableRef CVar_DebugMovement(
	TEXT("CM.DebugMovement"), ACMCharacter::DebugMovement,
	TEXT("Draw movement function debug geometry"),
	ECVF_Cheat);

int32 ACMCharacter::DebugAttacks = 0;
FAutoConsoleVariableRef CVar_DebugAttacks(
	TEXT("CM.DebugAttacks"), ACMCharacter::DebugAttacks,
	TEXT("Draw attack debug geometry"),
	ECVF_Cheat);

ACMCharacter::ACMCharacter(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCMCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	RootComponent = GetCapsuleComponent();

	bAlwaysRelevant = true;
	// ReplicatedMovement.RotationQuantizationLevel = ERotatorQuantization::ByteComponents;
	// ReplicatedMovement.VelocityQuantizationLevel = EVectorQuantization::RoundWholeNumber;
	// ReplicatedMovement.LocationQuantizationLevel = EVectorQuantization::RoundOneDecimal;

	// Cache tags
	HitDirectionFrontTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Front"));
	HitDirectionBackTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Back"));
	HitDirectionRightTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Right"));
	HitDirectionLeftTag = FGameplayTag::RequestGameplayTag(FName("Effect.HitReact.Left"));
	DeadTag = FGameplayTag::RequestGameplayTag(GAMEPLAYTAG_DEAD);
	EffectNotCanceledOnDeath = FGameplayTag::RequestGameplayTag(GAMEPLAYEFFECT_NOTCANCELEDONDEATH);
}

UCMCharacterStatusBarWidget* ACMCharacter::GetUIStatusBar()
{
	return UIStatusBar;
}

void ACMCharacter::InitializeUIStatusBar()
{
	// Only create once, dont create a floating status bar for yourself
	if (UIStatusBar || !AbilitySystemComponent.IsValid() || IsLocallyControlled())
	{
		return;
	}

	// Setup UI for Locally Owned Players only, not AI or the server's copy of the PlayerControllers
	ACMPlayerController * PC = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->IsLocalPlayerController())
	{
		if (UICharacterStatusBarClass)
		{
			UIStatusBar = CreateWidget<UCMCharacterStatusBarWidget>(PC, UICharacterStatusBarClass);
			if (UIStatusBar && UIStatusBarComp)
			{
				UIStatusBarComp->SetWidget(UIStatusBar);

				// Setup the floating status bar
				UIStatusBar->TargetCharacter = this;
				UIStatusBar->SetHealthPercentage(GetHealth() / GetMaxHealth());
				UIStatusBar->SetManaPercentage(GetMana() / GetMaxMana());
			}
		}
	}
}

// target system
bool ACMCharacter::IsTargetable_Implementation() const
{
	return IsAlive();
}

void ACMCharacter::OnUntargeted_Implementation()
{
	if (UIStatusBar)
	{
		UIStatusBar->OnUntargeted();
	}
}

void ACMCharacter::OnTargeted_Implementation()
{
	if (UIStatusBar)
	{
		UIStatusBar->OnTargeted();
	}
}

// BEGIN template functions

UAbilitySystemComponent* ACMCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

bool ACMCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 ACMCharacter::GetAbilityLevel(ECMAbilityInputID AbilityID) const
{
	return 1;
}

void ACMCharacter::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = false;
}

ECMHitReactDirection ACMCharacter::GetHitReactDirection(const FVector& ImpactPoint)
{
	const FVector& ActorLocation = GetActorLocation();
	// PointPlaneDist is super cheap - 1 vector subtraction, 1 dot product.
	float DistanceToFrontBackPlane = FVector::PointPlaneDist(ImpactPoint, ActorLocation, GetActorRightVector());
	float DistanceToRightLeftPlane = FVector::PointPlaneDist(ImpactPoint, ActorLocation, GetActorForwardVector());


	if (FMath::Abs(DistanceToFrontBackPlane) <= FMath::Abs(DistanceToRightLeftPlane))
	{
		// Determine if Front or Back

		// Can see if it's left or right of Left/Right plane which would determine Front or Back
		if (DistanceToRightLeftPlane >= 0)
		{
			return ECMHitReactDirection::Front;
		}
		else
		{
			return ECMHitReactDirection::Back;
		}
	}
	else
	{
		// Determine if Right or Left

		if (DistanceToFrontBackPlane >= 0)
		{
			return ECMHitReactDirection::Right;
		}
		else
		{
			return ECMHitReactDirection::Left;
		}
	}

	return ECMHitReactDirection::Front;
}

void ACMCharacter::PlayHitReact_Implementation(FGameplayTag HitDirection, AActor* DamageCauser)
{
	if (IsAlive())
	{
		if (HitDirection == HitDirectionLeftTag)
		{
			ShowHitReact.Broadcast(ECMHitReactDirection::Left);
		}
		else if (HitDirection == HitDirectionFrontTag)
		{
			ShowHitReact.Broadcast(ECMHitReactDirection::Front);
		}
		else if (HitDirection == HitDirectionRightTag)
		{
			ShowHitReact.Broadcast(ECMHitReactDirection::Right);
		}
		else if (HitDirection == HitDirectionBackTag)
		{
			ShowHitReact.Broadcast(ECMHitReactDirection::Back);
		}
	}
}


bool ACMCharacter::PlayHitReact_Validate(FGameplayTag HitDirection, AActor* DamageCauser)
{
	return true;
}

float ACMCharacter::GetHealth() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetHealth();
	}

	return 0.0f;
}

float ACMCharacter::GetMaxHealth() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetMaxHealth();
	}

	return 0.0f;
}

float ACMCharacter::GetMana() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetMana();
	}

	return 0.0f;
}

float ACMCharacter::GetMaxMana() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetMaxMana();
	}

	return 0.0f;
}

float ACMCharacter::GetStamina() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetStamina();
	}

	return 0.0f;
}

float ACMCharacter::GetMaxStamina() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetMaxStamina();
	}

	return 0.0f;
}

float ACMCharacter::GetMoveSpeed() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetMoveSpeed();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Character attribute set is invalid!"));
	}

	return 0.0f;
}

float ACMCharacter::GetMoveSpeedBaseValue() const
{
	if (CharacterAttributeSet.IsValid())
	{
		return CharacterAttributeSet->GetMoveSpeedAttribute().GetGameplayAttributeData(CharacterAttributeSet.Get())->GetBaseValue();
	}

	return 0.0f;
}

int32 ACMCharacter::GetCharacterLevel() const
{
	return 1;
}

// Run on Server and all clients
void ACMCharacter::Die()
{
	// Only runs on Server
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);
	GetMovementComponent()->StopMovementImmediately();

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAllAbilities();

		FGameplayEffectQuery EffectsCanceledOnDeathQuery = FGameplayEffectQuery::MakeQuery_MatchNoEffectTags(
			FGameplayTagContainer(EffectNotCanceledOnDeath));
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffects(EffectsCanceledOnDeathQuery);
		UE_LOG(LogTemp, Warning, TEXT("%s effects canceled on death"), *FString::FromInt(NumEffectsRemoved));
		AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(GAMEPLAYTAG_DEAD));
	}

	SetActorEnableCollision(false);

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void ACMCharacter::FinishDying()
{
	// 	// ragdoll logic -- need to make a lot of changes to character mesh before this works
	//	DetachFromControllerPendingDestroy();
	// 	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	// 	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	// 
	// 	bReplicateMovement = false;

	// 	UCharacterMovementComponent* MovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	// 	if (MovementComp)
	// 	{
	// 		MovementComp->StopMovementImmediately();
	// 		MovementComp->DisableMovement();
	// 		MovementComp->SetComponentTickEnabled(false);
	// 	}
	// 	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	// 	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	// 	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	// 	GetMesh()->SetAllBodiesSimulatePhysics(true);
	// 	GetMesh()->SetSimulatePhysics(true);
	// 	GetMesh()->WakeAllRigidBodies();
	// 	GetMesh()->bBlendPhysics = true;
	Destroy();
}

void ACMCharacter::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UCMGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void ACMCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing AbilitySystemComponent for %s."), TEXT(__FUNCTION__), *GetName());
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), TEXT(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void ACMCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
}

void ACMCharacter::SetHealth(float Health)
{
	if (CharacterAttributeSet.IsValid())
	{
		CharacterAttributeSet->SetHealth(Health);
	}
}

void ACMCharacter::SetMana(float Mana)
{
	if (CharacterAttributeSet.IsValid())
	{
		CharacterAttributeSet->SetMana(Mana);
	}
}

void ACMCharacter::SetStamina(float Stamina)
{
	if (CharacterAttributeSet.IsValid())
	{
		CharacterAttributeSet->SetStamina(Stamina);
	}
}

// END template functions

void ACMCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACMCharacter::GetMovementDirections(ECMMovementDirection& Primary, ECMMovementDirection& Secondary)
{
	FVector MovementNormal = RelativeVelocityNormalized();
	Primary = GetMovementDirection();

	if (Primary == ECMMovementDirection::Forward || Primary == ECMMovementDirection::Backward)
	{
		Secondary = MovementNormal.X >= 0.f ? ECMMovementDirection::Right : ECMMovementDirection::Left;
	}
	else
	{
		Secondary = MovementNormal.Y >= 0.f ? ECMMovementDirection::Forward : ECMMovementDirection::Backward;
	}
}

bool ACMCharacter::IsMoving()
{
	return GetVelocity().Size() > 0 || !GetLastMovementInputVector().IsZero();
}

// static -- returns relative velocity vector
// bounds X: left/right (-1, 1) Y: forward/back (-1, 1) Z (0)
FVector ACMCharacter::RelativeVelocityNormalized()
{
	if (GetVelocity().Size() < 0.001)
	{
		return FVector::ZeroVector;
	}

	FRotator RelativeRotation = UKismetMathLibrary::NormalizedDeltaRotator(
		GetActorRotation(), GetVelocity().Rotation());

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(RelativeRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(RelativeRotation);

	return FVector(RightVector.X, ForwardVector.X, 0.f);
}

float ACMCharacter::ForwardToLateralVelocityRelativeWeight()
{
	FVector ActorVelocityNormalAbs = RelativeVelocityNormalized().GetAbs();
	return ActorVelocityNormalAbs.Rotation().Yaw / 90.f;
}

float ACMCharacter::GetRelativeYawFromDirection(ECMMovementDirection Direction)
{
	const float RelativeYaw = GetRelativeRotation().Yaw;
	switch (Direction) {
	case ECMMovementDirection::Forward:
		return RelativeYaw;
	case ECMMovementDirection::Backward:
		return RelativeYaw - FMath::Sign(RelativeYaw) * 180.f;
	case ECMMovementDirection::Left:
		return RelativeYaw + 90.f;
	default: // Right
		return RelativeYaw - 90.f;
	}
}

float ACMCharacter::GetStartTimeFromDistanceCurve(UAnimSequence* Sequence)
{
	float CurveTime = 0.f;
	float DistanceLookup = (ExpectedStopLocation() - GetActorLocation()).Size();
	float CurveDistance = TNumericLimits<float>::Max();
	FRawCurveTracks CurvesOfAnim = Sequence->GetCurveData();
	TArray<FFloatCurve> Curves = CurvesOfAnim.FloatCurves;
	for (FFloatCurve& Curve : Curves)
	{
		if (Curve.Name.DisplayName == "DistanceCurve")
		{
			TArray<float> OutTimes, OutValues;
			Curve.GetKeys(OutTimes, OutValues);
			for (int32 i = 0; i < OutTimes.Num(); ++i)
			{
				float DistanceCandidate = FMath::Abs(FMath::Abs(OutValues[i]) - DistanceLookup);
				if (DistanceCandidate < CurveDistance)
				{
					CurveDistance = DistanceCandidate;
					CurveTime = OutTimes[i];
				}
			}
		}
	}
	// animation debugging
// 	UE_LOG(LogTemp, Warning, TEXT(
// 		"Distance: %s -- CurveDistance: %s -- CurveTime: %s"),
// 		*FString::SanitizeFloat(DistanceLookup), *FString::SanitizeFloat(CurveDistance), *FString::SanitizeFloat(CurveTime));
	return CurveTime;
}

// calculate expected stop location when player stops accelerating
// taken from https://answers.unrealengine.com/questions/531204/predict-stop-position-of-character-ahead-in-time.html
FVector ACMCharacter::ExpectedStopLocation()
{
	UCharacterMovementComponent* MC = Cast<UCharacterMovementComponent>(GetMovementComponent());
	// checkf(MC->BrakingDecelerationWalking <= 500.f, TEXT("Animation logic incompatible with high BrakingDecelerationWalking, use gravity/friction instead"))

	FPredictProjectilePathResult PredictResult;
	FPredictProjectilePathParams PredictParams;

	PredictParams.OverrideGravityZ = MC->GetGravityZ();
	PredictParams.LaunchVelocity = MC->Velocity;
	PredictParams.StartLocation = GetActorLocation();
	PredictParams.TraceChannel = ECollisionChannel::ECC_WorldStatic;
	PredictParams.bTraceWithChannel = true;
	PredictParams.bTraceWithCollision = true;
	PredictParams.ProjectileRadius = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	PredictParams.ActorsToIgnore.Add(this);
	
	UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult);
	
	if (IsDebugMovementEnabled())
	{
		DrawDebugSphere(GetWorld(), PredictResult.LastTraceDestination.Location, 30.f, 15, FColor::Red, false);
	}

	return PredictResult.LastTraceDestination.Location;
}

FRotator ACMCharacter::GetRelativeRotation()
{
	return UKismetMathLibrary::NormalizedDeltaRotator(GetVelocity().Rotation(), GetActorRotation());
}

ECMMovementDirection ACMCharacter::GetMovementDirection()
{
	if (!IsMoving()) return ECMMovementDirection::Forward;

	FVector ActorVelocityNormal = RelativeVelocityNormalized();
	if (ForwardToLateralVelocityRelativeWeight() > 0.45f)
	{
		return ActorVelocityNormal.Y >= 0.f ? ECMMovementDirection::Forward : ECMMovementDirection::Backward;
	}
	else {
		return ActorVelocityNormal.X >= 0.f ? ECMMovementDirection::Right : ECMMovementDirection::Left;
	}
}

float ACMCharacter::GetFloorSlope()
{
	const FVector FloorTraceEnd = GetActorLocation() + FRotator(-70.f, GetActorRotation().Yaw, 0.f).Vector() * 100.f;

	// UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, FHitResult& OutHit, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	const UCapsuleComponent* MyCapsuleComp = GetCapsuleComponent();

	FHitResult HitResult;
	const float TraceSphereRadius = 30.f;
	bool bDidFindFloorAhead = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(), GetActorLocation(), FloorTraceEnd, TraceSphereRadius,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false, ActorsToIgnore,
		DebugMovement > 0 ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		HitResult, true);

	const FVector FloorLocation = GetActorLocation() - FVector(0.f, 0.f, MyCapsuleComp->GetScaledCapsuleHalfHeight());

	if (!bDidFindFloorAhead) return 0.f;

	const float ErrorConstant = 5.5545f;

	return UKismetMathLibrary::GetDirectionUnitVector(FloorLocation, HitResult.ImpactPoint).Rotation().Pitch + ErrorConstant;
}

void ACMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// pawn capsule sweep. maxhitdistance by default is a multiple of actor's capsule radius
TArray<FHitResult> ACMCharacter::MeleeHitTrace(float AngleFromFront /*= 60.f*/, float MaxHitDistance /*= -1.f*/)
{
	// default hit distance 
	float MeleeCapsuleRadius = MaxHitDistance < 0.f ? GetCapsuleComponent()->GetScaledCapsuleRadius() * 6 : MaxHitDistance;
	AngleFromFront = AngleFromFront < 0.f ? 180.f : AngleFromFront;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	TArray<FHitResult> HitResults;

	EDrawDebugTrace::Type DebugTraceType = EDrawDebugTrace::None;

	if (DebugAttacks > 0)
	{
		DebugTraceType = EDrawDebugTrace::ForDuration;

		// draw forward arrow
		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorRotation().Vector() * MeleeCapsuleRadius, 2.f, FColor::Blue, true, 1.f);
		if (AngleFromFront < 180.f) {
			// left arrow
			DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorRotation().Add(0.f, -AngleFromFront, 0.f).Vector() * MeleeCapsuleRadius, 2.f, FColor::Blue, true, 1.f);
			// right arrow
			DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorRotation().Add(0.f, AngleFromFront, 0.f).Vector() * MeleeCapsuleRadius, 2.f, FColor::Blue, true, 1.f);
		}
	}

	bool bDidHit = UKismetSystemLibrary::CapsuleTraceMulti(
		GetWorld(), GetActorLocation(), GetActorLocation() - FVector(0.f, 0.f, 0.01f), MeleeCapsuleRadius, GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
		UEngineTypes::ConvertToTraceType(COLLISION_DAMAGE), false,  ActorsToIgnore, DebugTraceType, HitResults, true, FLinearColor::Red, FLinearColor::Green, 2.f);

	TSet<ACMCharacter*> HitCharacters;
	TArray<FHitResult> MeleeHitResults;

	for (FHitResult HitResult : HitResults)
	{
		if (HitResult.GetActor() == nullptr) continue;
		ACMCharacter* CharacterHit = Cast<ACMCharacter>(HitResult.GetActor());
		if (CharacterHit && !HitCharacters.Contains(CharacterHit))
		{
			float ImpactAngle = UKismetMathLibrary::NormalizedDeltaRotator((HitResult.ImpactPoint - GetActorLocation()).GetSafeNormal2D().Rotation(), GetActorRotation()).Yaw;
			if (FMath::Abs(ImpactAngle) <= AngleFromFront)
			{
				HitCharacters.Add(CharacterHit);
				// These values are used downstream by gameplay cues
				HitResult.Distance = (GetActorLocation() - HitResult.ImpactPoint).Size();
				HitResult.Location = HitResult.ImpactPoint;
				HitResult.Normal = HitResult.ImpactNormal;
				MeleeHitResults.Add(HitResult);
			}

			if (DebugAttacks > 0)
			{
				UE_LOG(LogTemp, Log, TEXT("%s: MeleeHitTrace: %s hit %s at distance %s/%s and angle %s/%s"),
					*FString(GetLocalRole() == ROLE_Authority ? "Server" : "Client"), *this->GetName(), *CharacterHit->GetName(),
					*FString::SanitizeFloat(HitResult.Distance), *FString::SanitizeFloat(MeleeCapsuleRadius),
					*FString::SanitizeFloat(ImpactAngle), *FString::SanitizeFloat(AngleFromFront));
			}
		}
	}

	return MeleeHitResults;
}
