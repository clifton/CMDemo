#include "CMPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "UI/CMPlayerStatusBarWidget.h"
#include "WidgetComponent.h"
#include "CMPlayerState.h"
#include "CMPlayerController.h"
#include "AI/CMPlayerAIController.h"
#include "CMGameModeBase.h"
#include "CrimsonMirror.h"


ACMPlayerCharacter::ACMPlayerCharacter(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// set our turn rates for input
	// 	BaseTurnRate = 45.f;
	// 	BaseLookUpRate = 45.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 68.492264));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->FieldOfView = 80.0f;

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

	// Makes sure that the animations play on the Server so that we can use bone and socket transforms
	// to do things like spawning projectiles and other FX.
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

	// Do we still need this?
	// 	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	// create weapon component
	UIPlayerStatusBarComp = CreateDefaultSubobject<UWidgetComponent>(FName("UICMPlayerStatusBarComponent"));
	UIPlayerStatusBarComp->SetupAttachment(RootComponent);
	UIPlayerStatusBarComp->SetRelativeLocation(FVector(0, 0, 120));
	UIPlayerStatusBarComp->SetWidgetSpace(EWidgetSpace::Screen);
	UIPlayerStatusBarComp->SetDrawSize(FVector2D(500, 500));

	UIPlayerStatusBarClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/GASDocumentation/UI/UI_FloatingStatusBar_Hero.UI_FloatingStatusBar_Hero_C"));
	if (!UIPlayerStatusBarClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find UIPlayerStatusBarClass. If it was moved, please update the reference location in C++."), TEXT(__FUNCTION__));
	}

	AIControllerClass = ACMPlayerAIController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
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
			FRotator DesiredYaw = GetDesiredRotation();
			FRotator RotateTo = FMath::RInterpTo(CurrentYaw, DesiredYaw, DeltaTime, InterpSpeed);
			RotateTo.Pitch = CharacterRotation.Pitch;
			RotateTo.Roll = CharacterRotation.Roll;
			SetActorRotation(RotateTo);
		}
	}
}

const FRotator ACMPlayerCharacter::GetDesiredRotation()
{
	FRotator DesiredRotation = CharacterAimRotation;
	DesiredRotation.Pitch = 0.f;
	DesiredRotation.Roll = 0.f;
	return DesiredRotation;
}

void ACMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

 	PlayerInputComponent->BindAxis("MoveForward", this, &ACMPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACMPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACMPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACMPlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &ACMPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACMPlayerCharacter::TurnRate);

	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent,
		FGameplayAbilityInputBinds(FString("Confirm"), FString("Cancel"), FString("ECMAbilityInputID"),
		static_cast<int32>(ECMAbilityInputID::Confirm), static_cast<int32>(ECMAbilityInputID::Cancel)));
}

// Server only
void ACMPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ACMPlayerState* PS = GetPlayerState<ACMPlayerState>();
	if (PS)
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent = Cast<UCMAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		// Set the AttributeSetBase for convenience attribute functions
		CharacterAttributeSet = PS->GetCharacterAttributeSet();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that possession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		InitializeAttributes();

		AddStartupEffects();

		AddCharacterAbilities();

		ACMPlayerController* PC = Cast<ACMPlayerController>(GetController());
		if (PC)
		{
			PC->CreateHUD();
		}

		InitializePlayerStatusBar();

		// Respawn specific things that won't affect first possession.

		// Forcibly set the DeadTag count to 0
		AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

		// Set Health/Mana/Stamina to their max. This is only necessary for *Respawn*.
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
		SetStamina(GetMaxStamina());
	}
}

USpringArmComponent* ACMPlayerCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* ACMPlayerCharacter::GetFollowCamera()
{
	return FollowCamera;
}

float ACMPlayerCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomArmLength;
}

FVector ACMPlayerCharacter::GetStartingCameraBoomLocation()
{
	return StartingCameraBoomLocation;
}

UCMPlayerStatusBarWidget* ACMPlayerCharacter::GetPlayerStatusBar()
{
	return UIPlayerStatusBar;
}

void ACMPlayerCharacter::FinishDying()
{
	if (Role == ROLE_Authority)
	{
		ACMGameModeBase* GM = Cast<ACMGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GM)
		{
			GM->PlayerDied(GetController());
		}
	}

	Super::FinishDying();
}

void ACMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Only needed for Heroes placed in world and when the player is the Server.
	// On respawn, they are set up in PossessedBy.
	// When the player a client, the floating status bars are all set up in OnRep_PlayerState.
	InitializePlayerStatusBar();

	// attach weapon to socket here

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = FollowCamera->RelativeLocation;

	// @HACK do we need this old hack?
	// AbilitySystem->InitAbilityActorInfo(this, this);
}

void ACMPlayerCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void ACMPlayerCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void ACMPlayerCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void ACMPlayerCharacter::TurnRate(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
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

void ACMPlayerCharacter::InitializePlayerStatusBar()
{
	// Only create once
	if (UIPlayerStatusBar || !AbilitySystemComponent.IsValid())
	{
		return;
	}

	// Setup UI for Locally Owned Players only, not AI or the server's copy of the PlayerControllers
	ACMPlayerController* PC = Cast<ACMPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->IsLocalPlayerController())
	{
		if (UIPlayerStatusBarClass)
		{
			UIPlayerStatusBar = CreateWidget<UCMPlayerStatusBarWidget>(PC, UIPlayerStatusBarClass);
			if (UIPlayerStatusBar && UIPlayerStatusBarComp)
			{
				UIPlayerStatusBarComp->SetWidget(UIPlayerStatusBar);

				// Setup the floating status bar
				UIPlayerStatusBar->SetHealthPercentage(GetHealth() / GetMaxHealth());
				UIPlayerStatusBar->SetManaPercentage(GetMana() / GetMaxMana());
			}
		}
	}
}

// Client only
void ACMPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ACMPlayerState* PS = GetPlayerState<ACMPlayerState>();
	if (PS)
	{
		// Set the ASC for clients. Server does this in PossessedBy.
		AbilitySystemComponent = Cast<UCMAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// Refresh ASC Actor Info for clients. Server will be refreshed by its AI/PlayerController when it possesses a new Actor.
		AbilitySystemComponent->RefreshAbilityActorInfo();

		// Set the AttributeSetBase for convenience attribute functions
		CharacterAttributeSet = PS->GetCharacterAttributeSet();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that posession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		InitializeAttributes();

		ACMPlayerController* PC = Cast<ACMPlayerController>(GetController());
		if (PC)
		{
			PC->CreateHUD();
		}

		// Simulated on proxies don't have their PlayerStates yet when BeginPlay is called so we call it again here
		InitializePlayerStatusBar();

		// Respawn specific things that won't affect first possession.

		// Forcibly set the DeadTag count to 0
		AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

		// Set Health/Mana/Stamina to their max. This is only necessary for *Respawn*.
		SetHealth(GetMaxHealth());
		SetMana(GetMaxMana());
		SetStamina(GetMaxStamina());
	}
}

void ACMPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ACMPlayerCharacter, CharacterAcceleration, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(ACMPlayerCharacter, CharacterAimRotation, COND_SkipOwner);
}