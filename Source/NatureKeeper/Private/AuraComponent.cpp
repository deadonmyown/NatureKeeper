#include "AuraComponent.h"

#include "AuraManager.h"
#include "EditorCategoryUtils.h"
#include "NatureKeeperGameMode.h"
#include "Effects/EffectBase.h"


UAuraComponent::UAuraComponent()
{
}

void UAuraComponent::BeginPlay()
{
	Super::BeginPlay();

	AuraManager = GetWorld()->GetAuthGameMode<ANatureKeeperGameMode>()->GetAuraManager();
	AuraManager->RegisterAura(this);
}

void UAuraComponent::ChangeAuraEffects_Implementation(const EAuraType NewAuraType)
{
	if (AuraType == NewAuraType)
		return;

	AuraType = NewAuraType;

	ApplyAuraEffect();
}

void UAuraComponent::ApplyAuraEffect_Implementation()
{
	//For now like this, player trying to change aura on good, enemies on evil. Later refactor this code
	if (AuraType == EAuraType::AT_Good)
	{
		for (int i = 0; i < EvilEffects.Num(); i++)
		{
			EvilEffects[i]->CancelEffect();
		}

		TArray<TScriptInterface<UAffectable>> AffectedActors = AuraManager->GetAffectedObjects();

		for (int i = 0; i < GoodEffects.Num(); i++)
		{
			GoodEffects[i]->ApplyEffect(AffectedActors);
		}
	}
	else
	{
		for (int i = 0; i < GoodEffects.Num(); i++)
		{
			GoodEffects[i]->CancelEffect();
		}

		TArray<TScriptInterface<UAffectable>> AffectedActors = AuraManager->GetAffectedObjects();

		for (int i = 0; i < EvilEffects.Num(); i++)
		{
			EvilEffects[i]->ApplyEffect(AffectedActors);
		}
	}
}

void UAuraComponent::UpdateAuraEffect_Implementation()
{
	if (AuraType == EAuraType::AT_Good)
	{
		TArray<TScriptInterface<UAffectable>> AffectedActors = AuraManager->GetAffectedObjects();

		for (int i = 0; i < GoodEffects.Num(); i++)
		{
			GoodEffects[i]->ApplyEffect(AffectedActors);
		}
	}
	else
	{
		TArray<TScriptInterface<UAffectable>> AffectedActors = AuraManager->GetAffectedObjects();

		for (int i = 0; i < EvilEffects.Num(); i++)
		{
			EvilEffects[i]->ApplyEffect(AffectedActors);
		}
	}
}

void UAuraComponent::CancelAuraEffect_Implementation()
{
	for (int i = 0; i < EvilEffects.Num(); i++)
	{
		EvilEffects[i]->CancelEffect();
	}
	
	for (int i = 0; i < GoodEffects.Num(); i++)
	{
		GoodEffects[i]->CancelEffect();
	}
}
