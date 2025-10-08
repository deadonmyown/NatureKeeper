// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/DamageableEffectFactory.h"

#include "Effects/DamageableEffect.h"

UEffectBase* UDamageableEffectFactory::CreateEffect()
{
	UDamageableEffect* NewEffect = NewObject<UDamageableEffect>(this);
	NewEffect->EffectDataAsset = EffectDataAsset;
	NewEffect->EffectFactory = this;
	return NewEffect;
}
