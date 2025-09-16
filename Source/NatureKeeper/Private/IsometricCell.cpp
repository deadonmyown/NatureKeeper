#include "NatureKeeper/Public/IsometricCell.h"


AIsometricCell::AIsometricCell()
{
}

void AIsometricCell::BeginPlay()
{
	Super::BeginPlay();
}

void AIsometricCell::SetCostToStart(int32 NewCost)
{
	CostToStart = NewCost;
}

void AIsometricCell::SetCostToTarget(int32 NewCost)
{
	CostToTarget = NewCost;
}

void AIsometricCell::SetPathConnection(AIsometricCell* NewConnection)
{
	PathConnection = NewConnection;
}

void AIsometricCell::SetPathNodeCoord(FIntVector2D NewCoord)
{
	PathNodeCoord = NewCoord;
}

int32 AIsometricCell::GetDistanceToOtherCell(AIsometricCell* OtherPath)
{
	return FMath::Abs(PathNodeCoord.X - OtherPath->GetPathNodeCoord().X) + FMath::Abs(PathNodeCoord.Y - OtherPath->GetPathNodeCoord().Y);
}

void AIsometricCell::StartInteract_Implementation(ACharacter* InteractionInvoker)
{
	//TODO: Add methods for cellmovable interface to move our character
}

void AIsometricCell::StopInteract_Implementation(ACharacter* InteractionInvoker)
{
	
}

