#include "InteractionSystem/NaturalSpring.h"

#include "NatureKeeperCharacter.h"
#include "InteractionSystem/NaturalSpringPowerSource.h"
#include "ResourceSystem/EvilComponent.h"
#include "ResourceSystem/HealthComponent.h"


ANaturalSpring::ANaturalSpring()
{
	EvilComponent = CreateDefaultSubobject<UEvilComponent>("EvilComponent");
	
	PrimaryActorTick.bCanEverTick = false;

	bIsAbsorbComplete = false;
}

void ANaturalSpring::OnAbsorbComplete(int MinEvilValue)
{
	bIsAbsorbComplete = true;
	GetWorld()->GetTimerManager().ClearTimer(EvilAbsorbTimer);
	InteractingPlayerCache = nullptr;
}

void ANaturalSpring::OnAbsorbEvil()
{
	if (bIsAbsorbComplete) return;
	
	if (!InteractingPlayerCache) return;

	if (!CheckPowerSourcesConditions()) return;

	if (InteractingPlayerCache->GetEvilComponent()->GetMaxResourceValue() == InteractingPlayerCache->GetEvilComponent()->GetResourceValue()) return;
	
	EvilComponent->DecreaseResourceValue(1);
	InteractingPlayerCache->GetEvilComponent()->IncreaseResourceValue(1);
	
	if (OnNaturalSpringEvilAbsorb.IsBound())
		OnNaturalSpringEvilAbsorb.Broadcast(this, 1);
}

void ANaturalSpring::BeginPlay()
{
	Super::BeginPlay();

	EvilComponent->OnResourceValueReachMin.AddDynamic(this, &ANaturalSpring::OnAbsorbComplete);
}

bool ANaturalSpring::CheckPowerSourcesConditions() const
{
	if (NaturalSpringPowerSources.IsEmpty()) return true;

	for (int i = 0; i < NaturalSpringPowerSources.Num(); i++)
	{
		if (!NaturalSpringPowerSources[i]->bIsPowerSourceRevived)
			return false;
	}
	
	return true;
}

bool ANaturalSpring::StartInteract_Implementation(AActor* InteractionInvoker)
{
	if (bIsAbsorbComplete) return false;

	if (!CheckPowerSourcesConditions()) return false;
	
	if (ANatureKeeperCharacter* InteractionPlayer = Cast<ANatureKeeperCharacter>(InteractionInvoker))
	{
		InteractingPlayerCache = InteractionPlayer;
		GetWorld()->GetTimerManager().SetTimer(EvilAbsorbTimer, this, &ANaturalSpring::OnAbsorbEvil, EvilAbsorbTimeInSec, true);
		return true;
	}

	return false;
}

bool ANaturalSpring::StopInteract_Implementation(AActor* InteractionInvoker)
{
	if (ANatureKeeperCharacter* InteractionPlayer = Cast<ANatureKeeperCharacter>(InteractionInvoker))
	{
		GetWorld()->GetTimerManager().ClearTimer(EvilAbsorbTimer);
		InteractingPlayerCache = nullptr;
		return true;
	}
	
	return false;
}