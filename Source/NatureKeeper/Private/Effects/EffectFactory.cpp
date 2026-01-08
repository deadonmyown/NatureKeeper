#include "Effects/EffectFactory.h"

#include "Effects/EffectBase.h"
#include "Effects/Data/EffectDataAsset.h"
#include "Effects/Data/TickableDamageableEffectDataAsset.h"

UEffectBase* UEffectFactory::CreateEffect()
{
	UEffectBase* NewEffect = NewObject<UEffectBase>(this, EffectClass);

	if (!NewEffect->InitEffect(EffectDataAsset))
		return nullptr;

	NewEffect->OnComplete.AddDynamic(this, &UEffectFactory::RemoveEffect);
	NewEffect->OnFail.AddDynamic(this, &UEffectFactory::RemoveEffect);
	AddEffect(NewEffect);
	
	return NewEffect;
}

void UEffectFactory::AddEffect(UEffectBase* EffectToAdd)
{
	if (Effects.Contains(EffectToAdd))
		return;

	Effects.Add(EffectToAdd);
}

void UEffectFactory::RemoveEffect(UEffectBase* EffectToRemove)
{
	if (!Effects.Contains(EffectToRemove))
		return;

	Effects.Remove(EffectToRemove);
}

TArray<UEffectBase*>& UEffectFactory::GetEffects()
{
	return Effects;
}

float UEffectFactory::GetEffectCompletionTime()
{
	if (UTickableDamageableEffectDataAsset* TickableDataAsset = Cast<UTickableDamageableEffectDataAsset>(EffectDataAsset))
	{
		return TickableDataAsset->TicksCount * TickableDataAsset->TickAmount;
	}
	return 0.0f;
}
