#include "UI/CMCharacterStatusBarWidget.h"
#include "CMCharacter.h"


UCMCharacterStatusBarWidget::UCMCharacterStatusBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxRenderDistance = 2500.f;
	MinimumScaleVisible = 0.2f;
}

float UCMCharacterStatusBarWidget::GetRenderScale()
{
	if (TargetCharacter)
	{
		float Distance = TargetCharacter->GetDistanceTo(GetOwningPlayerPawn());
		return FMath::Clamp(1 - Distance / MaxRenderDistance, 0.f, 1.f);
	}
	
	return 0.f;
}

bool UCMCharacterStatusBarWidget::bShouldRenderCheckDistance()
{
	return GetRenderScale() >= MinimumScaleVisible;
}
