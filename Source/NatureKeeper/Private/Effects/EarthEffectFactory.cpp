#include "Effects/EarthEffectFactory.h"

#include "Effects/EarthEffect.h"
#include "Effects/Data/EarthEffectDataAsset.h"

UEffectBase* UEarthEffectFactory::CreateEffect()
{
	UEarthEffect* NewEffect = NewObject<UEarthEffect>(this);
	UEarthEffectDataAsset* EarthEffectDataAsset = Cast<UEarthEffectDataAsset>(EffectDataAsset);

	if (!EarthEffectDataAsset)
		return nullptr;
	
	NewEffect->EffectVFX = EarthEffectDataAsset->EffectVFX;
	NewEffect->EffectElementType = EarthEffectDataAsset->EffectElementType;
	NewEffect->DamageAmount = EarthEffectDataAsset->DamageAmount;
	NewEffect->EffectFactory = this;
	return NewEffect;
}

