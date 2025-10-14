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

	BlockCells();
}

void UCellPlacementComponent::OnRegister()
{
	Super::OnRegister();

	/*if (MainCell)
	{
		GetOwner()->SetActorLocation(MainCell->GetNavigationRoot()->GetComponentLocation());
	}*/
}

void UCellPlacementComponent::FreeCells()
{
	for (int i = 0; i < CellBlocked.Num(); i++)
	{
		CellBlocked[i]->CellType = ECellType::ICT_Default;
	}
}

void UCellPlacementComponent::BlockCells()
{
	for (int i = 0; i < CellBlocked.Num(); i++)
	{
		CellBlocked[i]->CellType = ECellType::ICT_Block;
	}
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

