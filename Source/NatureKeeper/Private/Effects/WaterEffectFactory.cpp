// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/WaterEffectFactory.h"

#include "Effects/WaterEffect.h"
#include "Effects/Data/WaterEffectDataAsset.h"

UEffectBase* UWaterEffectFactory::CreateEffect()
{
	UWaterEffect* NewEffect = NewObject<UWaterEffect>(this);
	UWaterEffectDataAsset* WaterDataAsset = Cast<UWaterEffectDataAsset>(EffectDataAsset);

	if (!WaterDataAsset)
		return nullptr;
	
	NewEffect->EffectVFX = WaterDataAsset->EffectVFX;
	NewEffect->EffectElementType = WaterDataAsset->EffectElementType;
	NewEffect->InitialDamageAmount = WaterDataAsset->InitialDamageAmount;
	NewEffect->TickDamageAmount = WaterDataAsset->TickDamageAmount;
	NewEffect->TicksCount = WaterDataAsset->TicksCount;
	NewEffect->TickAmount = WaterDataAsset->TickAmount;
	NewEffect->TickEffectVFX = WaterDataAsset->TickEffectVFX;
	NewEffect->SteamInitialDamageAmount = WaterDataAsset->SteamInitialDamageAmount;
	NewEffect->SteamEffectVFX = WaterDataAsset->SteamEffectVFX;
	NewEffect->EffectFactory = this;
	return NewEffect;
}
