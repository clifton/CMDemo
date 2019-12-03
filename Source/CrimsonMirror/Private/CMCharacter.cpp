#include "CMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimSequence.h"
#include "Net/UnrealNetwork.h"


// console variables
int32 ACMCharacter::DebugMovement = 0;
FAutoConsoleVariableRef CVar_DebugMovement(
	TEXT("CM.DebugMovement"), ACMCharacter::DebugMovement,
	TEXT("Draw movement function debug geometry"),
	ECVF_Cheat);

ACMCharacter::ACMCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	SpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetIsReplicated(true);

	CreateDefaultSubobject<UCMCharacterAttributeSet>(TEXT("AttributeSet"));

	SetReplicates(true);
	bReplicateMovement = true;

	ReplicatedMovement.RotationQuantizationLevel = ERotatorQuantization::ByteComponents;
	ReplicatedMovement.VelocityQuantizationLevel = EVectorQuantization::RoundWholeNumber;
	ReplicatedMovement.LocationQuantizationLevel = EVectorQuantization::RoundOneDecimal;
}

void ACMCharacter::BeginPlay()
{
	Super::BeginPlay();

	UCharacterMovementComponent* MC = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MC->BrakingDecelerationWalking > 500.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Animation logic incompatible with high BrakingDecelerationWalking, use gravity/friction instead"));
		MC->BrakingDecelerationWalking = 200.f;
	}
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
	UE_LOG(LogTemp, Warning, TEXT(
		"Distance: %s -- CurveDistance: %s -- CurveTime: %s"),
		*FString::SanitizeFloat(DistanceLookup), *FString::SanitizeFloat(CurveDistance), *FString::SanitizeFloat(CurveTime));
	return CurveTime;
}

// calculate expected stop location when player stops accelerating
// taken from https://answers.unrealengine.com/questions/531204/predict-stop-position-of-character-ahead-in-time.html
FVector ACMCharacter::ExpectedStopLocation()
{
	UCharacterMovementComponent* MC = Cast<UCharacterMovementComponent>(GetMovementComponent());
	checkf(MC->BrakingDecelerationWalking <= 500.f, TEXT("Animation logic incompatible with high BrakingDecelerationWalking, use gravity/friction instead"))

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