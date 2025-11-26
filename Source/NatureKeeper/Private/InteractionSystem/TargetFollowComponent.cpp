#include "InteractionSystem/TargetFollowComponent.h"

#include "Interfaces/Target.h"


UTargetFollowComponent::UTargetFollowComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UTargetFollowComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UTargetFollowComponent::SetTarget(TScriptInterface<UTarget> NewTarget)
{
	Target = NewTarget;
}

void UTargetFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Target || !Target.GetObject()) return;

	//Right now just simple set actor location, after we should interpolate position, include gravitation and physics in our computation etc.
	GetOwner()->SetActorLocation(ITarget::Execute_GetTargetLocation(Target.GetObject()));
}

