#include "Cell.h"

#include "ResourceSystem/EvilComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/CellMovable.h"


ACell::ACell()
{
	EvilComponent = CreateDefaultSubobject<UEvilComponent>("EvilComponent");
}

void ACell::BeginPlay()
{
	Super::BeginPlay();

	EvilComponent->OnResourceValueReachMin.AddDynamic(this, &ACell::OnMinEvilEnergyValueReach);
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

void ACell::ClearPathfinding()
{
	CostToStart = 0;
	CostToTarget = 0;
	PathConnection = nullptr;
}

USceneComponent* ACell::GetNavigationRoot_Implementation()
{
	return RootComponent;
}

//Change material cell color
void ACell::OnMinEvilEnergyValueReach_Implementation(int MinValue)
{
	
}

bool ACell::StartInteract_Implementation(AActor* InteractionInvoker)
{
	return false;
}

bool ACell::StopInteract_Implementation(AActor* InteractionInvoker)
{
	if (InteractionInvoker->Implements<UCellMovable>())
	{
		return ICellMovable::Execute_TryMoveByCells(InteractionInvoker, {this});
	}
	return false;
}

bool ACell::StartVisit_Implementation(const TScriptInterface<UVisitor>& Visitor)
{
	return true;
}

bool ACell::EndVisit_Implementation(const TScriptInterface<UVisitor>& Visitor)
{
	return true;
}

bool ACell::RegisterEffect_Implementation(UEffectBase* EffectToAdd)
{
	if (Effects.Contains(EffectToAdd))
		return false;

	Effects.Add(EffectToAdd);
	return true;
}

bool ACell::UnregisterEffect_Implementation(UEffectBase* EffectToRemove)
{
	if (!Effects.Contains(EffectToRemove))
		return false;

	Effects.Remove(EffectToRemove);
	return true;
}

FVector ACell::GetEffectLocation_Implementation()
{
	return GetNavigationRoot()->GetComponentLocation();
}

