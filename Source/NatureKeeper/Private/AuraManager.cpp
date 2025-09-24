#include "AuraManager.h"

#include "AuraComponent.h"

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

	NewAura->ApplyAuraEffect();
	
	return true;
}

bool AAuraManager::UnregisterAura(UAuraComponent* AuraToRemove)
{
	if (!Auras.Contains(AuraToRemove))
		return false;

	Auras.Remove(AuraToRemove);

	AuraToRemove->CancelAuraEffect();
	
	return true;
}

bool AAuraManager::RegisterAffectedObject(TScriptInterface<UAffectable> NewObject)
{
	if (AffectedObjects.Contains(NewObject))
		return false;

	AffectedObjects.Add(NewObject);

	for (int i = 0; i < Auras.Num(); i++)
	{
		Auras[i]->UpdateAuraEffect();
	}
	
	return true;
}

bool AAuraManager::UnregisterAffectedObject(TScriptInterface<UAffectable> NewObject)
{
	if (!AffectedObjects.Contains(NewObject))
		return false;

	AffectedObjects.Remove(NewObject);
	return true;
}

