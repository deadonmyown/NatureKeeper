// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/DamageableEffectFactory.h"

#include "Effects/DamageableEffect.h"
#include "Effects/Data/DamageableEffectDataAsset.h"

UEffectBase* UDamageableEffectFactory::CreateEffect()
{
	UDamageableEffect* NewEffect = NewObject<UDamageableEffect>(this);
	UDamageableEffectDataAsset* DamageableDataAsset = Cast<UDamageableEffectDataAsset>(EffectDataAsset);

	if (!DamageableDataAsset)
		return nullptr;
	
	NewEffect->EffectVFX = DamageableDataAsset->EffectVFX;
	NewEffect->EffectElementType = DamageableDataAsset->EffectElementType;
	NewEffect->DamageAmount = DamageableDataAsset->DamageAmount;
	NewEffect->EffectFactory = this;
	return NewEffect;
}
