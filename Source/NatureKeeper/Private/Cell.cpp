#include "Cell.h"

#include "ResourceSystem/EvilComponent.h"
#include "Managers/WinEntityComponent.h"


ACell::ACell()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	EvilComponent = CreateDefaultSubobject<UEvilComponent>("EvilComponent");

	WinEntityComponent = CreateDefaultSubobject<UWinEntityComponent>("WinEntityComponent");
}

void ACell::BeginPlay()
{
	Super::BeginPlay();

	EvilComponent->OnResourceValueReachMin.AddDynamic(this, &ACell::OnMinEvilEnergyValueReach);
	if (EvilComponent->GetResourceValue() == EvilComponent->GetMinResourceValue())
		OnMinEvilEnergyValueReach(EvilComponent->GetMinResourceValue());
}

//Change material cell color
void ACell::OnMinEvilEnergyValueReach_Implementation(int MinValue)
{
	WinEntityComponent->ClearEntity();
}

USceneComponent* ACell::GetNavigationRoot_Implementation()
{
	return RootComponent;
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

