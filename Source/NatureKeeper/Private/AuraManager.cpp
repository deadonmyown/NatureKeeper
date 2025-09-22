#include "AuraManager.h"

AAuraManager::AAuraManager()
{
}

void AAuraManager::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AAuraManager::RegisterAura(UAuraComponent* NewAura)
{
	if (Auras.Contains(NewAura))
		return false;

	Auras.Add(NewAura);
	return true;
}

bool AAuraManager::UnregisterAura(UAuraComponent* NewAura)
{
	if (!Auras.Contains(NewAura))
		return false;

	Auras.Remove(NewAura);
	return true;
}

bool AAuraManager::RegisterAffectedActor(AActor* NewActor)
{
	if (AffectedActors.Contains(NewActor))
		return false;

	AffectedActors.Add(NewActor);
	return true;
}

bool AAuraManager::UnregisterAffectedActor(AActor* NewActor)
{
	if (!AffectedActors.Contains(NewActor))
		return false;

	AffectedActors.Remove(NewActor);
	return true;
}

