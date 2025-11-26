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
	NewEffect->InitialDamageAmount = WindEffectDataAsset->InitialDamageAmount;
	NewEffect->TickDamageAmount = WindEffectDataAsset->TickDamageAmount;
	NewEffect->TicksCount = WindEffectDataAsset->TicksCount;
	NewEffect->TickAmount = WindEffectDataAsset->TickAmount;
	NewEffect->TickEffectVFX = WindEffectDataAsset->TickEffectVFX;
	NewEffect->EffectFactory = this;
	return NewEffect;
}
