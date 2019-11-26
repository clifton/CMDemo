#include "CMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"


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

bool ACMCharacter::IsMoving()
{
	return GetVelocity().Size() > 0 || !GetLastMovementInputVector().IsZero();
}

// static -- returns relative velocity vector
// bounds X: left/right (-1, 1) Y: forward/back (-1, 1) Z (0)
FVector ACMCharacter::RelativeVelocityNormalized(AActor* Actor)
{
	if (Actor == nullptr || Actor->GetVelocity().Size() < 0.001)
	{
		return FVector::ZeroVector;
	}

	FRotator RelativeRotation = UKismetMathLibrary::NormalizedDeltaRotator(
		Actor->GetActorRotation(), Actor->GetVelocity().Rotation());

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(RelativeRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(RelativeRotation);

	return FVector(RightVector.X, ForwardVector.X, 0.f);
}

float ACMCharacter::ForwardToLateralVelocityRelativeWeight(AActor* Actor)
{
	FVector ActorVelocityNormalAbs = RelativeVelocityNormalized(Actor).GetAbs();
	return ActorVelocityNormalAbs.Rotation().Yaw / 90.f;
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

ECMMovementDirection ACMCharacter::GetMovementDirection()
{
	if (!IsMoving()) return ECMMovementDirection::Forward;

	FVector ActorVelocityNormal = RelativeVelocityNormalized(this);
	if (ForwardToLateralVelocityRelativeWeight(this) > 0.45f)
	{
		return ActorVelocityNormal.Y >= 0.f ? ECMMovementDirection::Forward : ECMMovementDirection::Backward;
	}
	else {
		return ActorVelocityNormal.X >= 0.f ? ECMMovementDirection::Right : ECMMovementDirection::Left;
	}
}

void ACMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementDirection = GetMovementDirection();
}