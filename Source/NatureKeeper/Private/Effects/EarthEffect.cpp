#include "Effects/EarthEffect.h"

#include "NatureKeeperUtils.h"
#include "Effects/Data/EarthEffectDataAsset.h"
#include "Interfaces/Movable.h"
#include "Managers/PhysicsManager.h"

bool UEarthEffect::InitEffect(const FEffectData& InEffectData)
{
	const UEarthEffectDataAsset* EarthEffectDataAsset = Cast<UEarthEffectDataAsset>(InEffectData.EffectDataAsset);

	if (!EarthEffectDataAsset)
		return false;
	
	EffectVFX = EarthEffectDataAsset->EffectVFX;
	EffectElementType = EarthEffectDataAsset->EffectElementType;
	BlendingEffectDataMap = EarthEffectDataAsset->BlendingEffectDataMap;
	DamageAmount = EarthEffectDataAsset->DamageAmount;
	SlowPercent = EarthEffectDataAsset->SlowPercent;
	SlowTime = EarthEffectDataAsset->SlowTime;
	StunTime = EarthEffectDataAsset->StunTime;
	
	return true;
}

bool UEarthEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(DamageAmount);

	if (InAffectedObject.GetObject()->Implements<UMovable>())
	{
		if (APhysicsManager* PM = UNatureKeeperUtils::GetPhysicsManager(this))
		{
			PM->StartSlowActor(InAffectedObject.GetObject(), SlowPercent, SlowTime, StunTime);
		}
	}
	
	UE_LOG(LogTemp, Display, TEXT("Damageable Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), DamageAmount);

	//Immediately cancel because this is one shot effect
	CancelEffect();
	
	return true;
}
