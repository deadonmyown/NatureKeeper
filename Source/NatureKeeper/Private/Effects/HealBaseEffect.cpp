// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/HealBaseEffect.h"

#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

bool UHealBaseEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UEffectBase::ApplyEffect(InAffectedObject))
		return false;

	bIsResist = IAffectable::Execute_GetResistEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType);
	
	return true;
}

bool UHealBaseEffect::TryHeal(int InHealAmount, int InHealMultiplier)
{
	if (InHealAmount <= 0 || InHealMultiplier <= 0 || !AffectedObject.GetObject() || !AffectedObject.GetObject()->Implements<UDamageable>())
		return false;

	IDamageable::Execute_Heal(AffectedObject.GetObject(),
		bIsResist ? InHealAmount * InHealMultiplier : InHealAmount);
	return true;
}

