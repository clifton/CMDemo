#include "CMPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"


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

	NetUpdateFrequency = 66.0f;
	MinNetUpdateFrequency = 33.0f;

	ReplicatedMovement.RotationQuantizationLevel = ERotatorQuantization::ShortComponents;
	ReplicatedMovement.VelocityQuantizationLevel = EVectorQuantization::RoundTwoDecimals;
	ReplicatedMovement.LocationQuantizationLevel = EVectorQuantization::RoundTwoDecimals;
}

void ACMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// should rotate player pawn
	if (Role >= ROLE_AutonomousProxy)
	{
		// is this worth it?
		CharacterAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
		CharacterAimRotation = GetControlRotation();

		if (CharacterAcceleration.Size() > 0)
		{
			float InterpSpeed = 8.f;
			const FRotator CharacterRotation = GetActorRotation();
			FRotator CurrentYaw = FRotator(0.f, CharacterRotation.Yaw, 0.f);
			FRotator DesiredYaw = FRotator(0.f, GetDesiredRotation().Yaw, 0.f);
			FRotator RotateTo = FMath::RInterpTo(CurrentYaw, DesiredYaw, DeltaTime, InterpSpeed);
			RotateTo.Pitch = CharacterRotation.Pitch;
			RotateTo.Roll = CharacterRotation.Roll;
			SetActorRotation(RotateTo);
		}
	}
}

void ACMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystem->InitAbilityActorInfo(this, this);
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
	FRotator DesiredRotation = CharacterAimRotation;
	DesiredRotation.Pitch = 0.f;
	DesiredRotation.Roll = 0.f;
	return DesiredRotation;
}

void ACMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, );

 	PlayerInputComponent->BindAxis("MoveForward", this, &ACMPlayerCharacter::MoveForward);
 	PlayerInputComponent->BindAxis("MoveRight", this, &ACMPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACMPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACMPlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACMPlayerCharacter::Jump);

	DECLARE_DELEGATE_OneParam(FAbilitySelectDelegate, EAbilityMap);
	PlayerInputComponent->BindAction<FAbilitySelectDelegate>("PrimaryAttack", IE_Pressed, this, &ACMPlayerCharacter::BeginAbility, EAbilityMap::PrimaryAttack);
	PlayerInputComponent->BindAction<FAbilitySelectDelegate>("PrimaryAttack", IE_Released, this, &ACMPlayerCharacter::EndAbility, EAbilityMap::PrimaryAttack);
}

void ACMPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ACMPlayerCharacter, CharacterAcceleration, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(ACMPlayerCharacter, CharacterAimRotation, COND_SkipOwner);
}