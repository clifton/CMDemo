#include "AI/CMAIController.h"
#include "AI/CMAICharacter.h"


ACMAIController::ACMAIController()
{
	// if we end up needing a player state
	// bWantsPlayerState = true;
}

// Server only
void ACMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ACMAICharacter* AICharacter = Cast<ACMAICharacter>(InPawn);
	if (!AICharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid type for AI to possess: %s"), *InPawn->GetName());
		return;
	}
}