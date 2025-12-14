#include "TargetSystem/TargetStrategy.h"

bool UTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (bIsStarted)
		return false;
	
	bIsStarted = true;
	return true;
}

void UTargetStrategy::UpdateStrategy(float DeltaTime)
{
}

void UTargetStrategy::CancelStrategy()
{
	bIsStarted = false;
}
