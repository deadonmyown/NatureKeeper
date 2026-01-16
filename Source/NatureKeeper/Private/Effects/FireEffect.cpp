#include "Effects/FireEffect.h"

#include "NatureKeeperUtils.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/FireEffectDataAsset.h"
#include "Interfaces/Affectable.h"

bool UFireEffect::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	UFireEffectDataAsset* FireDataAsset = Cast<UFireEffectDataAsset>(InEffectDataAsset);

	if (!FireDataAsset)
		return false;
	
	EffectVFX = FireDataAsset->EffectVFX;
	EffectElementType = FireDataAsset->EffectElementType;
	BlendingEffectClass = InEffectDataAsset->BlendingEffectClass;
	BlendingEffectDataAsset = InEffectDataAsset->BlendingEffectDataAsset;
	BlendingEffectElementType = InEffectDataAsset->BlendingEffectElementType;
	InitialDamageAmount = FireDataAsset->InitialDamageAmount;
	TickDamageAmount = FireDataAsset->TickDamageAmount;
	TicksCount = FireDataAsset->TicksCount;
	TickAmount = FireDataAsset->TickAmount;
	TickEffectVFX = FireDataAsset->TickEffectVFX;

	CurrTick = 0;
	return true;
}
