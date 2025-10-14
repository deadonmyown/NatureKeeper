// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/FireEffectFactory.h"

#include "Effects/FireEffect.h"
#include "Effects/Data/FireEffectDataAsset.h"

UEffectBase* UFireEffectFactory::CreateEffect()
{
	UFireEffect* NewEffect = NewObject<UFireEffect>(this);
	UFireEffectDataAsset* FireDataAsset = Cast<UFireEffectDataAsset>(EffectDataAsset);

	if (!FireDataAsset)
		return nullptr;
	
	NewEffect->EffectVFX = FireDataAsset->EffectVFX;
	NewEffect->EffectElementType = FireDataAsset->EffectElementType;
	NewEffect->InitialDamageAmount = FireDataAsset->InitialDamageAmount;
	NewEffect->TickDamageAmount = FireDataAsset->TickDamageAmount;
	NewEffect->TicksCount = FireDataAsset->TicksCount;
	NewEffect->TickAmount = FireDataAsset->TickAmount;
	NewEffect->TickEffectVFX = FireDataAsset->TickEffectVFX;
	NewEffect->SteamInitialDamageAmount = FireDataAsset->SteamInitialDamageAmount;
	NewEffect->SteamEffectVFX = FireDataAsset->SteamEffectVFX;
	NewEffect->EffectFactory = this;
	return NewEffect;
}
