#include "ResourceSystem/EntityResourceComponent.h"


UEntityResourceComponent::UEntityResourceComponent()
{
	
}


void UEntityResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEntityResourceComponent::SetResourceValue(int NewValue)
{
	ResourceValue = NewValue;
}

void UEntityResourceComponent::IncreaseResourceValue(int DeltaValue)
{
	int OldValue = ResourceValue;
	bool bReachedMax = false;
	if (ResourceValue + DeltaValue >= MaxResourceValue)
	{
		ResourceValue = MaxResourceValue;
		bReachedMax = true;
	}
	else
	{
		ResourceValue += DeltaValue;
	}

	if (OnResourceValueChanged.IsBound())
	{
		OnResourceValueChanged.Broadcast(OldValue, ResourceValue);
	}

	if (bReachedMax && OnResourceValueReachMax.IsBound())
	{
		OnResourceValueReachMax.Broadcast(MaxResourceValue);
	}
}

void UEntityResourceComponent::DecreaseResourceValue(int DeltaValue)
{
	int OldValue = ResourceValue;
	bool bReachedMin = false;
	if (ResourceValue - DeltaValue <= MinResourceValue)
	{
		ResourceValue = MinResourceValue;
		bReachedMin = true;
	}
	else
	{
		ResourceValue -= DeltaValue;
	}
	
	if (OnResourceValueChanged.IsBound())
	{
		OnResourceValueChanged.Broadcast(OldValue, ResourceValue);
	}

	if (bReachedMin && OnResourceValueReachMin.IsBound())
	{
		OnResourceValueReachMin.Broadcast(MinResourceValue);
	}
}


	