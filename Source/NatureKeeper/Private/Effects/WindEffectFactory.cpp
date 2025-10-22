#include "Effects/WindEffectFactory.h"

#include "Effects/WindEffect.h"
#include "Effects/Data/WindEffectDataAsset.h"

UEffectBase* UWindEffectFactory::CreateEffect()
{
	UWindEffect* NewEffect = NewObject<UWindEffect>(this);
	UWindEffectDataAsset* WindEffectDataAsset = Cast<UWindEffectDataAsset>(EffectDataAsset);

	if (!WindEffectDataAsset)
		return nullptr;
	
	NewEffect->EffectVFX = WindEffectDataAsset->EffectVFX;
	NewEffect->EffectElementType = WindEffectDataAsset->EffectElementType;
	NewEffect->DamageAmount = WindEffectDataAsset->DamageAmount;
	NewEffect->EffectFactory = this;
	return NewEffect;
}
