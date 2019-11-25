#include "CMCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


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
	// return ActorVelocityNormalAbs.Rotation() / 90.f;
	// float RelativeVelocityYaw = UKismetMathLibrary::MakeRotationFromAxes(ActorVelocityNormalAbs).Yaw;
	return ActorVelocityNormalAbs.Rotation().Yaw / 90.f;
}

// calculate expected stop location when player stops accelerating
// taken from https://answers.unrealengine.com/questions/531204/predict-stop-position-of-character-ahead-in-time.html
FVector ACMCharacter::ExpectedStopLocation()
{
	UCharacterMovementComponent* MC = Cast<UCharacterMovementComponent>(GetMovementComponent());
	GetWorld()->GetDeltaSeconds();

	// Small number break loop when velocity is less than this value
	float Local_WorldDeltaSecond = UGameplayStatics::GetWorldDeltaSeconds(this);

	float SmallVelocity = 10.f * FMath::Square(Local_WorldDeltaSecond);
	
	float Friction = FMath::Max(0.f, MC->bUseSeparateBrakingFriction ? MC->BrakingFriction : MC->GroundFriction * MC->BrakingFrictionFactor);

	// Current velocity at current frame in unit/frame
	FVector CurrentVelocityInFrame = MC->Velocity * Local_WorldDeltaSecond;

	// Store velocity direction for later use
	FVector CurrentVelocityDirection = MC->Velocity.GetSafeNormal2D();

	// Current deacceleration at current frame in unit/fame^2
	FVector CurrentDeaccelerationInFrame = (CurrentVelocityDirection * MC->BrakingDecelerationWalking) * FMath::Square(Local_WorldDeltaSecond);

	// float variable use to store distance to targeted stop location
	float StoppingDistance = 0.f;
	int StopFrameCount = CurrentVelocityInFrame.Size() / CurrentDeaccelerationInFrame.Size();

	// Do Stop calculation go through all frames and calculate stop distance in each frame and stack them
	for (int i = 0; i <= StopFrameCount; i++)
	{
		//Update velocity
		
		CurrentVelocityInFrame -= CurrentDeaccelerationInFrame;

		// if velocity in XY plane is small break loop for safety
		if (CurrentVelocityInFrame.Size2D() <= SmallVelocity)
		{
			// UE_LOG(LogTemp, Warning, TEXT("Took %s steps"), *FString::FromInt(i));
			break;
		}

		// Calculate distance travel in current frame and add to previous distance
		StoppingDistance += CurrentVelocityInFrame.Size2D();
	}

	FVector ExpectedLocation = GetActorLocation() + CurrentVelocityDirection * StoppingDistance;
	// return stopping distance from player position in previous frame
	// DrawDebugSphere(GetWorld(), ExpectedLocation, 30.f, 15, FColor::Red, false, 3.0f);
	return ExpectedLocation;
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