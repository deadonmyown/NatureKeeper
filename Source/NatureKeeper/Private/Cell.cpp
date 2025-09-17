#include "Cell.h"

#include "NatureKeeperUtils.h"
#include "GameFramework/Character.h"
#include "Interfaces/CellMovable.h"


ACell::ACell()
{
}

void ACell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACell::SetCostToStart(int32 NewCost)
{
	CostToStart = NewCost;
}

void ACell::SetCostToTarget(int32 NewCost)
{
	CostToTarget = NewCost;
}

void ACell::SetPathConnection(ACell* NewConnection)
{
	PathConnection = NewConnection;
}

void ACell::SetPathNodeCoord(FIntVector2D NewCoord)
{
	PathNodeCoord = NewCoord;
}

int32 ACell::GetDistanceToOtherCell(ACell* OtherPath)
{
	return FMath::Abs(PathNodeCoord.X - OtherPath->GetPathNodeCoord().X) + FMath::Abs(PathNodeCoord.Y - OtherPath->GetPathNodeCoord().Y);
}

void ACell::StartInteract_Implementation(ACharacter* InteractionInvoker)
{
	
}

void ACell::StopInteract_Implementation(ACharacter* InteractionInvoker)
{
	if (InteractionInvoker->Implements<UCellMovable>())
	{
		if (ACell* StartCell = ICellMovable::Execute_GetCurrentCell(InteractionInvoker))
		{
			TArray<ACell*> Path = UNatureKeeperUtils::FindPath(StartCell, this);
			if (Path.Num() > 0)
				ICellMovable::Execute_MoveByPath(InteractionInvoker, Path);
		}
	}
}

