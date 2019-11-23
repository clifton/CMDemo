#include "CMPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"


ACMPlayerCharacter::ACMPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 92.f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// set our turn rates for input
	// 	BaseTurnRate = 45.f;
	// 	BaseLookUpRate = 45.f;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void ACMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// should rotate player pawn
	if (IsMoving())
	{
		float InterpSpeed = 8.f;
		FRotator CurrentYaw = FRotator(0.f, GetActorRotation().Yaw, 0.f);
		FRotator DesiredYaw = FRotator(0.f, GetDesiredRotation().Yaw, 0.f);
		FRotator RotateTo = FMath::RInterpTo(CurrentYaw, DesiredYaw, DeltaTime, InterpSpeed);
		RotateTo.Pitch = GetActorRotation().Pitch;
		RotateTo.Roll = GetActorRotation().Roll;
		SetActorRotation(RotateTo);
	}
}

void ACMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACMPlayerCharacter::MoveForward(float Velocity)
{
	FVector TargetForwardVector = UKismetMathLibrary::GetForwardVector(GetDesiredRotation());
	AddMovementInput(TargetForwardVector * Velocity);
}

void ACMPlayerCharacter::MoveRight(float Velocity)
{
	FVector TargetRightVector = UKismetMathLibrary::GetRightVector(GetDesiredRotation());
	AddMovementInput(TargetRightVector * Velocity);
}

FRotator ACMPlayerCharacter::GetDesiredRotation()
{
	return GetControlRotation();
}

void ACMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, );

 	PlayerInputComponent->BindAxis("MoveForward", this, &ACMPlayerCharacter::MoveForward);
 	PlayerInputComponent->BindAxis("MoveRight", this, &ACMPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACMPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACMPlayerCharacter::AddControllerYawInput);
}
