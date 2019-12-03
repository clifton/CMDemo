#pragma once

#include "CoreMinimal.h"
#include "CMCharacter.h"
#include "CMPlayerCharacter.generated.h"


UCLASS()
class CRIMSONMIRROR_API ACMPlayerCharacter : public ACMCharacter
{
	GENERATED_BODY()
	
public:
	ACMPlayerCharacter();

protected:
	virtual void BeginPlay() override;

	// handle input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float Velocity);
	void MoveRight(float Velocity);

public:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector CharacterAcceleration;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FRotator GetDesiredRotation();
};
