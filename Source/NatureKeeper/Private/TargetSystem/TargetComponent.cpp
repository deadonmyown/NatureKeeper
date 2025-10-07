#include "TargetSystem/TargetComponent.h"

#include "TargetSystem/TargetStrategy.h"

UTargetComponent::UTargetComponent()
{
	TargetStrategy = nullptr;
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTargetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetStrategy && TargetStrategy->GetIsTargeting())
	{
		TargetStrategy->UpdateStrategy();
	}
}

void UTargetComponent::SetTargetStrategy(UTargetStrategy* NewTargetStrategy)
{
	if (TargetStrategy)
		CancelTargetStrategy();
	
	TargetStrategy = NewTargetStrategy;
}

void UTargetComponent::ClearTargetStrategy()
{
	TargetStrategy = nullptr;
}

void UTargetComponent::CancelTargetStrategy()
{
	if (TargetStrategy)
	{
		TargetStrategy->CancelStrategy();
		TargetStrategy = nullptr;
	}
}


