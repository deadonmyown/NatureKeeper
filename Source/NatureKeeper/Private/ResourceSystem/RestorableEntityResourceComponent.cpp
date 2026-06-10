#include "ResourceSystem/RestorableEntityResourceComponent.h"


URestorableEntityResourceComponent::URestorableEntityResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void URestorableEntityResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (RestoreAmount > 0 && RestoreDelayInSec > 0.0f)
		GetWorld()->GetTimerManager().SetTimer(RestoreTimer, this, &URestorableEntityResourceComponent::OnRestore, RestoreDelayInSec, true);
}

void URestorableEntityResourceComponent::OnRestore()
{
	if (ResourceValue >= MaxResourceValue)
		return;

	IncreaseResourceValue(RestoreAmount);
}
