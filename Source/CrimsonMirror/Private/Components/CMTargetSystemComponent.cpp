#include "Components/CMTargetSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/CMTargetableInterface.h"
#include "Player/CMPlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/CMPlayerController.h"
#include "DrawDebugHelpers.h"


int32 UCMTargetSystemComponent::DebugTargeting = 0;
FAutoConsoleVariableRef CVar_DebugTargeting(
	TEXT("CM.DebugTargeting"), UCMTargetSystemComponent::DebugTargeting,
	TEXT("Draw targeting debug geometry"),
	ECVF_Cheat);

UCMTargetSystemComponent::UCMTargetSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// tick maximum of 10 times per second
	PrimaryComponentTick.TickInterval = 0.1f;
	bAutoRegister = true;
}

void UCMTargetSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

ACMPlayerCharacter* UCMTargetSystemComponent::GetPlayer()
{
	return Cast<ACMPlayerCharacter>(GetOwner());
}

void UCMTargetSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

TArray<TPair<AActor*, float>> UCMTargetSystemComponent::GetTargets()
{
	const float TraceDistance = 2200.f;
	const float TraceRadius = 400.f;
	TSet<AActor*> CheckedActors;
	TArray<TPair<AActor*, float>> HitActorScores;

	const FVector TraceBegin = GetPlayer()->GetFollowCamera()->GetComponentLocation(); // GetPlayer()->GetActorLocation();
	const FVector TraceEnd = GetPlayer()->GetActorLocation() + GetPlayer()->GetFollowCamera()->GetForwardVector() * TraceDistance;

	const auto DebugTraceType = DebugTargeting > 0 ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetPlayer());
	TArray<FHitResult> HitResults;
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_Pawn) };

	bool bDidHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), TraceBegin, TraceEnd, TraceRadius,
		ObjectTypes, false, ActorsToIgnore, DebugTraceType,
		HitResults, true, FLinearColor::Red, FLinearColor::Green, 1.f);

	for (FHitResult HitResult : HitResults)
	{
		AActor* HitActor = HitResult.Actor.Get();
		if (HitActor == nullptr || CheckedActors.Contains(HitActor)) continue;
		CheckedActors.Add(HitActor);

		if (!TargetIsTargetable(HitActor) || !TargetInLineOfSight(HitActor) || !TargetIsVisible(HitActor)) continue;

		FVector CameraFwdVector = GetPlayer()->GetFollowCamera()->GetComponentTransform().GetRotation().GetForwardVector();
		const float DotProduct = -1.f * FVector::DotProduct(CameraFwdVector, HitResult.ImpactNormal);
		const float Score = 2.f * DotProduct + (1 - (HitResult.Distance / TraceDistance));
		// score function: 2 * DotProduct + (1 - (Distance/MaxDistance))
		HitActorScores.Add(TPair<AActor*, float>(HitActor, Score));

		if (DebugTargeting > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit %s - distance %s - dot %s - fwd vector %s - impactpoint %s"), *HitResult.Actor->GetName(),
				*FString::SanitizeFloat(GetPlayer()->GetDistanceTo(HitResult.Actor.Get())), *FString::SanitizeFloat(Score), *CameraFwdVector.ToString(), *HitResult.ImpactPoint.ToString());
		}
	}

	return HitActorScores;
}

void UCMTargetSystemComponent::GetTarget()
{
	auto HitActorScores = GetTargets();
	HitActorScores.Sort([](const TPair<AActor*, float>& A, const TPair<AActor*, float>& B) {
		return A.Value > B.Value;
	});

	AActor* NewTarget = HitActorScores.Num() == 0 ? nullptr : HitActorScores[0].Key;
	if (NewTarget != CurrentTarget) {
		ClearTarget();
		if (NewTarget) {
			Cast<ICMTargetableInterface>(NewTarget)->Execute_OnTargeted(NewTarget);
		}
		CurrentTarget = NewTarget;
	}
}

void UCMTargetSystemComponent::ClearTarget()
{
	if (CurrentTarget)
	{
		Cast<ICMTargetableInterface>(CurrentTarget)->Execute_OnUntargeted(CurrentTarget);
	}
	CurrentTarget = nullptr;
}

bool UCMTargetSystemComponent::TargetIsTargetable(AActor* Actor)
{
	ICMTargetableInterface* IsTargetable = Cast<ICMTargetableInterface>(Actor);
	if (IsTargetable)
	{
		return IsTargetable->Execute_IsTargetable(Actor);
	}

	return false;
}

// check if there is a line of sight to the target from the camera or the player pawn not blocked by ECC_WorldStatic
bool UCMTargetSystemComponent::TargetInLineOfSight(AActor* HitActor)
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	if (DebugTargeting > 0)
	{
		DrawDebugLine(GetWorld(), GetPlayer()->GetFollowCamera()->GetComponentLocation(), HitActor->GetActorLocation(), FColor::Cyan, false, 1.0f, (uint8)'\000', 2.0f);
		DrawDebugLine(GetWorld(), GetPlayer()->GetActorLocation(), HitActor->GetActorLocation(), FColor::Cyan, false, 1.0f, (uint8)'\000', 2.0f);
	}
	return !(
		GetWorld()->LineTraceTestByObjectType(GetPlayer()->GetFollowCamera()->GetComponentLocation(), HitActor->GetActorLocation(), QueryParams) &&
		GetWorld()->LineTraceTestByObjectType(GetPlayer()->GetActorLocation(), HitActor->GetActorLocation(), QueryParams)
	);
}

bool UCMTargetSystemComponent::TargetIsVisible(AActor* HitActor)
{
	ACMPlayerController* PlayerController = Cast<ACMPlayerController>(GetPlayer()->GetController());
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCMTargetSystemComponent::TargetIsVisible could not instantiate player controller for %s"), *GetPlayer()->GetName());
		return true;
	}

	FVector2D ScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(HitActor->GetActorLocation(), ScreenLocation);

	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	return ScreenLocation.X > 0 && ScreenLocation.Y > 0 && ScreenLocation.X < ViewportSizeX && ScreenLocation.Y < ViewportSizeY;
}

void UCMTargetSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
}
