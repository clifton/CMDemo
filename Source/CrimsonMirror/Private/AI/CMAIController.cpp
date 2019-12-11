#include "AI/CMAIController.h"


// Server only
void ACMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("AI: %s possessed by %s!"), *GetName(), *GetName());
}