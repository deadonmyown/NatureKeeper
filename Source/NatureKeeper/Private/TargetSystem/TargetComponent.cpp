#include "TargetSystem/TargetComponent.h"

#include "TargetSystem/TargetStrategy.h"

UTargetComponent::UTargetComponent()
{
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UTargetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TargetStrategy)
	{
		TargetStrategy->UpdateStrategy();
	}
}

void UTargetComponent::SetTargetStrategy(UTargetStrategy* NewTargetStrategy)
{
	TargetStrategy = NewTargetStrategy;
}

void UTargetComponent::ClearTargetStrategy()
{
	TargetStrategy = nullptr;
}


