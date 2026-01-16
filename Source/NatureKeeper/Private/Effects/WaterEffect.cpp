// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/WaterEffect.h"

#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/WaterEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

bool UWaterEffect::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	UWaterEffectDataAsset* WaterDataAsset = Cast<UWaterEffectDataAsset>(InEffectDataAsset);

	if (!WaterDataAsset)
		return false;
	
	EffectVFX = WaterDataAsset->EffectVFX;
	EffectElementType = WaterDataAsset->EffectElementType;
	BlendingEffectClass = InEffectDataAsset->BlendingEffectClass;
	BlendingEffectDataAsset = InEffectDataAsset->BlendingEffectDataAsset;
	BlendingEffectElementType = InEffectDataAsset->BlendingEffectElementType;
	InitialDamageAmount = WaterDataAsset->InitialDamageAmount;
	TickDamageAmount = WaterDataAsset->TickDamageAmount;
	TicksCount = WaterDataAsset->TicksCount;
	TickAmount = WaterDataAsset->TickAmount;
	TickEffectVFX = WaterDataAsset->TickEffectVFX;

	CurrTick = 0;
	return true;
}
