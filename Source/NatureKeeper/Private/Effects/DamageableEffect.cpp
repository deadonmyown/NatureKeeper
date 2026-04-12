// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/DamageableEffect.h"

#include "Effects/EffectFactory.h"
#include "Effects/Data/DamageableEffectDataAsset.h"
#include "Interfaces/Affectable.h"

bool UDamageableEffect::InitEffect(const FEffectData& EffectData)
{
	const UDamageableEffectDataAsset* DamageableDataAsset = Cast<UDamageableEffectDataAsset>(EffectData.EffectDataAsset);

	if (!DamageableDataAsset)
		return false;
	
	EffectVFX = DamageableDataAsset->EffectVFX;
	EffectElementType = DamageableDataAsset->EffectElementType;
	BlendingEffectDataMap = DamageableDataAsset->BlendingEffectDataMap;
	DamageAmount = DamageableDataAsset->DamageAmount;
	return true;
}

bool UDamageableEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(DamageAmount);

	UE_LOG(LogTemp, Display, TEXT("Damageable Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), DamageAmount);

	//Immediately cancel because this is one shot effect
	CancelEffect();
	
	return true;
}
