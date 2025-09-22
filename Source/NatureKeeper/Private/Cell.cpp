#include "Cell.h"

#include "AuraComponent.h"
#include "NatureKeeperUtils.h"
#include "GameFramework/Character.h"
#include "Interfaces/CellMovable.h"


ACell::ACell()
{
	AuraComponent = CreateDefaultSubobject<UAuraComponent>("AuraComponent");
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

USceneComponent* ACell::GetNavigationRoot_Implementation()
{
	return RootComponent;
}

bool ACell::StartInteract_Implementation(ACharacter* InteractionInvoker)
{
	return false;
}

bool ACell::StopInteract_Implementation(ACharacter* InteractionInvoker)
{
	if (InteractionInvoker->Implements<UCellMovable>())
	{
		return ICellMovable::Execute_TryMoveByCells(InteractionInvoker, this);
	}
	return false;
}

bool ACell::StartVisit_Implementation(TScriptInterface<UVisitor> Visitor)
{
	return true;
}

bool ACell::EndVisit_Implementation(TScriptInterface<UVisitor> Visitor)
{
	return true;
}

