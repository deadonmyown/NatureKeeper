#include "Effects/EffectFactory.h"

#include "Effects/EffectBase.h"
#include "Effects/Data/EffectDataAsset.h"

UEffectBase* UEffectFactory::CreateEffect()
{
	UEffectBase* NewEffect = NewObject<UEffectBase>(this);
	NewEffect->EffectVFX = EffectDataAsset->EffectVFX;
	NewEffect->EffectElementType = EffectDataAsset->EffectElementType;
	NewEffect->EffectFactory = this;
	return NewEffect;
}

bool UEffectFactory::AddEffect(UEffectBase* EffectToAdd)
{
	if (Effects.Contains(EffectToAdd))
		return false;

	Effects.Add(EffectToAdd);
	return true;
}
bool UEffectFactory::RemoveEffect(UEffectBase* EffectToRemove)
{
	if (!Effects.Contains(EffectToRemove))
		return false;

	Effects.Remove(EffectToRemove);
	return true;
}

TArray<UEffectBase*>& UEffectFactory::GetEffects()
{
	return Effects;
}