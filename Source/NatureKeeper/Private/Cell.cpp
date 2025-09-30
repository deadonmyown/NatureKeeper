#include "Cell.h"

#include "Effects/AbilityComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/CellMovable.h"


ACell::ACell()
{
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>("AbilityComponent");
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

bool ACell::StartVisit_Implementation(const TScriptInterface<UVisitor>& Visitor)
{
	if (Visitor.GetObject() && Visitor.GetObject()->Implements<UAffectable>())
	{
		AbilityComponent->ApplyAbilityEffect(Visitor.GetObject());
		return true;
	}
	return false;
}

bool ACell::EndVisit_Implementation(const TScriptInterface<UVisitor>& Visitor)
{
	return true;
}

