// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/DamageableEffect.h"

#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"

bool UDamageableEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
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

bool UDamageableEffect::CancelEffect()
{
	return Super::CancelEffect();
}
