#include "CellPlacementComponent.h"

#include "Cell.h"

UCellPlacementComponent::UCellPlacementComponent()
{
}

void UCellPlacementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MainCell)
	{
		GetOwner()->SetActorLocation(MainCell->GetNavigationRoot()->GetComponentLocation());
	}

	for (int i = 0; i < CellBlocked.Num(); i++)
	{
		CellBlocked[i]->CellType = ECellType::ICT_Block;
	}
}

void UCellPlacementComponent::OnRegister()
{
	Super::OnRegister();

	/*if (MainCell)
	{
		GetOwner()->SetActorLocation(MainCell->GetNavigationRoot()->GetComponentLocation());
	}*/
}

#if WITH_EDITOR
void UCellPlacementComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	/*if (MainCell)
	{
		GetOwner()->SetActorLocation(MainCell->GetNavigationRoot()->GetComponentLocation());
	}*/
}
#endif

