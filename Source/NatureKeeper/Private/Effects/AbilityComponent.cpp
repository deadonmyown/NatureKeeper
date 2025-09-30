#include "Effects/AbilityComponent.h"

#include "Effects/EffectBase.h"
#include "Effects/EffectFactory.h"

UAbilityComponent::UAbilityComponent()
{
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UAbilityComponent::CancelAbilityEffect_Implementation()
{
	TArray<UEffectFactory*> ActualEffectFactory = GetActualEffects();
	for (int i = 0; i < ActualEffectFactory.Num(); i++)
	{
		TArray<UEffectBase*> ActualEffects = ActualEffectFactory[i]->GetEffects();
		for (int j = ActualEffects.Num() - 1; j >= 0; j--)
		{
			ActualEffects[j]->CancelEffect();
		}
	}
}

void UAbilityComponent::UpdateAbilityEffect_Implementation()
{
}

void UAbilityComponent::ApplyAbilityEffect_Implementation(const TScriptInterface<UAffectable>& InAffectedObject)
{
	TArray<UEffectFactory*> ActualEffectFactory = GetActualEffects();
	for (int i = 0; i < ActualEffectFactory.Num(); i++)
	{
		UEffectBase* NewEffect = ActualEffectFactory[i]->CreateEffect();
		NewEffect->ApplyEffect(InAffectedObject);
	}
}

void UAbilityComponent::ChangeAbilityEffectsFactory_Implementation(EAbilityType NewType)
{
	if (AuraType == NewType)
		return;

	CancelAbilityEffect();

	AuraType = NewType;
}

