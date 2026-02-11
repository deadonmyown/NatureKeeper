#include "TargetSystem/TargetStrategy.h"

#include "Effects/Ability.h"
#include "TargetSystem/TargetComponent.h"

bool UTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (bIsStarted || !InAbility || !InTargetComponent)
		return false;

	Ability = InAbility;
	Ability->ChangeExtraManaCost(TargetStrategyManaCost);
	TargetComponent = InTargetComponent;

	bIsTargeting = false;
	
	bIsStarted = true;		
	return true;
}

void UTargetStrategy::UpdateStrategy(float DeltaTime)
{
}

void UTargetStrategy::CancelStrategy()
{
	bIsTargeting = false;
	bIsStarted = false;

	Ability->ChangeExtraManaCost(-TargetStrategyManaCost);
	Ability = nullptr;
	TargetComponent = nullptr;
}
