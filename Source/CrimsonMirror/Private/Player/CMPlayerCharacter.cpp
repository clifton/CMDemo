#include "CMPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"


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
}

void ACMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACMPlayerCharacter::MoveForward(float Velocity)
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	AddMovementInput(CameraComp->GetForwardVector() * Velocity);
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ACMPlayerCharacter::MoveRight(float Velocity)
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	AddMovementInput(CameraComp->GetRightVector() * Velocity);
	GetCharacterMovement()->bOrientRotationToMovement = false;
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
