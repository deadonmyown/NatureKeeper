// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/DamageableBaseEffect.h"

#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

bool UDamageableBaseEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!UEffectBase::ApplyEffect(InAffectedObject))
		return false;

	bIsWeakness = IAffectable::Execute_GetWeaknessEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType);
	
	return true;
}

bool UDamageableBaseEffect::TryDamage(int InDamageAmount, int InDamageMultiplier)
{
	if (InDamageAmount <= 0 || InDamageMultiplier <= 0 || !AffectedObject.GetObject() || !AffectedObject.GetObject()->Implements<UDamageable>())
		return false;

	IDamageable::Execute_TakeDamage(AffectedObject.GetObject(), bIsWeakness ? InDamageAmount * InDamageMultiplier : InDamageAmount);
	return true;
}
