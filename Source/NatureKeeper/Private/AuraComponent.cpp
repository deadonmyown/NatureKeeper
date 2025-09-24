#include "AuraComponent.h"

#include "AuraManager.h"
#include "NatureKeeperGameMode.h"
#include "Effects/EffectBase.h"
#include "Interfaces/EffectInterface.h"


UAuraComponent::UAuraComponent()
{
}

void UAuraComponent::BeginPlay()
{
	Super::BeginPlay();

	AuraManager = GetWorld()->GetAuthGameMode<ANatureKeeperGameMode>()->GetAuraManager();
	AuraManager->RegisterAura(this);
}

void UAuraComponent::ChangeAuraEffects_Implementation(const EAuraType NewAuraType, const TArray<UEffectBase*> NewEffects)
{
	if (AuraType == NewAuraType)
		return;

	AuraType = NewAuraType;
	
	for (int i = 0; i < Effects.Num(); i++)
	{
		IEffectInterface::Execute_CancelEffect(Effects[i]);
	}

	Effects = NewEffects;

	TArray<AActor*> AffectedActors = AuraManager->GetAffectedActors();

	for (int i = 0; i < Effects.Num(); i++)
	{
		for (int j = 0; j < AffectedActors.Num(); j++)
		{
			IEffectInterface::Execute_ApplyEffect(Effects[i], AffectedActors[j]);
		}
	}
}
