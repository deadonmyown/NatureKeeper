#include "CellPlacementComponent.h"

#include "Cell.h"

UCellPlacementComponent::UCellPlacementComponent()
{
}

void UCellPlacementComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCellPlacementComponent::OnRegister()
{
	Super::OnRegister();

	if (CellRef)
	{
		GetOwner()->SetActorLocation(CellRef->GetNavigationRoot()->GetComponentLocation());
	}
}

#if WITH_EDITOR
void UCellPlacementComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (CellRef)
	{
		GetOwner()->SetActorLocation(CellRef->GetNavigationRoot()->GetComponentLocation());
	}
}
#endif

