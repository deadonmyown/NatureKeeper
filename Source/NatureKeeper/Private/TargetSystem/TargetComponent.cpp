#include "TargetSystem/TargetComponent.h"

#include "TargetSystem/TargetStrategy.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickInterval = 0.5f;
	
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
		TargetStrategy->UpdateStrategy(DeltaTime);
	}
}

void UTargetComponent::SetTargetStrategy(UTargetStrategy* NewTargetStrategy)
{
	if (TargetStrategy)
		CancelTargetStrategy();
	
	TargetStrategy = NewTargetStrategy;
	
	if(OnTargetSet.IsBound())
		OnTargetSet.Broadcast(TargetStrategy);
}

void UTargetComponent::ClearTargetStrategy()
{
	TargetStrategy = nullptr;
	if(OnTargetClear.IsBound())
		OnTargetClear.Broadcast();
}

void UTargetComponent::CancelTargetStrategy()
{
	if (TargetStrategy)
	{
		TargetStrategy->CancelStrategy();
		TargetStrategy = nullptr;
	}
}


