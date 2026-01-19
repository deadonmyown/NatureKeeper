#include "TargetSystem/TargetStrategy.h"

#include "Effects/PlayerAbility.h"
#include "TargetSystem/TargetComponent.h"

bool UTargetStrategy::StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (bIsStarted)
		return false;

	Ability = InAbility;
	TargetComponent = InTargetComponent;

	TargetComponent->SetTargetStrategy(this);
	
	bIsStarted = true;		
	return true;
}

void UTargetStrategy::UpdateStrategy(float DeltaTime)
{
}

void UTargetStrategy::CancelStrategy(bool bClearAbility)
{
	bIsTargeting = false;
	bIsStarted = false;
	
	if (TargetComponent->GetTargetStrategy() == this)
	{
		TargetComponent->ClearTargetStrategy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetComponent already has another active target strategy, can't clear it"));
	}
	
	if (bClearAbility)
	{
		Ability->ClearEffectDataAssets();
		Ability->ClearTargetStrategy();
	}
	
	Ability = nullptr;
	TargetComponent = nullptr;
}
