// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/TickableDamageableEffectFactory.h"

#include "Effects/TickableDamageableEffect.h"
#include "Effects/Data/TickableDamageableEffectDataAsset.h"

UEffectBase* UTickableDamageableEffectFactory::CreateEffect()
{
	UTickableDamageableEffect* NewEffect = NewObject<UTickableDamageableEffect>(this);
	UTickableDamageableEffectDataAsset* TickableDataAsset = Cast<UTickableDamageableEffectDataAsset>(EffectDataAsset);

	if (!TickableDataAsset)
		return nullptr;
	
	NewEffect->EffectVFX = TickableDataAsset->EffectVFX;
	NewEffect->EffectElementType = TickableDataAsset->EffectElementType;
	NewEffect->InitialDamageAmount = TickableDataAsset->InitialDamageAmount;
	NewEffect->TickDamageAmount = TickableDataAsset->TickDamageAmount;
	NewEffect->TicksCount = TickableDataAsset->TicksCount;
	NewEffect->TickAmount = TickableDataAsset->TickAmount;
	NewEffect->TickEffectVFX = TickableDataAsset->TickEffectVFX;
	NewEffect->EffectFactory = this;
	return NewEffect;
}
