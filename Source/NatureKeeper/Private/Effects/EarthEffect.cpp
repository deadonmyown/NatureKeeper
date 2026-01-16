#include "Effects/EarthEffect.h"

#include "Effects/Data/EarthEffectDataAsset.h"

bool UEarthEffect::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	UEarthEffectDataAsset* EarthEffectDataAsset = Cast<UEarthEffectDataAsset>(InEffectDataAsset);

	if (!EarthEffectDataAsset)
		return false;
	
	EffectVFX = EarthEffectDataAsset->EffectVFX;
	EffectElementType = EarthEffectDataAsset->EffectElementType;
	BlendingEffectClass = InEffectDataAsset->BlendingEffectClass;
	BlendingEffectDataAsset = InEffectDataAsset->BlendingEffectDataAsset;
	BlendingEffectElementType = InEffectDataAsset->BlendingEffectElementType;
	DamageAmount = EarthEffectDataAsset->DamageAmount;

	return true;
}
