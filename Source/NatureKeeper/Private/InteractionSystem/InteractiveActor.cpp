#include "InteractionSystem/InteractiveActor.h"

#include "CellPlacementComponent.h"
#include "Interfaces/CellMovable.h"

AInteractiveActor::AInteractiveActor()
{
	CellPlacement = CreateDefaultSubobject<UCellPlacementComponent>("CellPlacement");
}

bool AInteractiveActor::StartInteract_Implementation(AActor* InteractionInvoker)
{
	if (InteractionInvoker->Implements<UCellMovable>())
	{
		return ICellMovable::Execute_TryMoveByCells(InteractionInvoker, CellPlacement->CellNeighbours);
	}
	return false;
}

bool AInteractiveActor::StopInteract_Implementation(AActor* InteractionInvoker)
{
	return true;
}