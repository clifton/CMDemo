#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CMTargetableInterface.generated.h"


UINTERFACE(Blueprintable)
class UCMTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

class CRIMSONMIRROR_API ICMTargetableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Target System")
	bool IsTargetable() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Target System")
	void OnTargeted();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Target System")
	void OnUntargeted();
};