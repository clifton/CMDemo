#include "CMCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"


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

void ACMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}