// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/WaterEffect.h"

#include "NatureKeeperUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/WaterEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/Movable.h"
#include "Managers/PhysicsManager.h"

bool UWaterEffect::InitEffect(const FEffectData& InEffectData)
{
	const UWaterEffectDataAsset* WaterDataAsset = Cast<UWaterEffectDataAsset>(InEffectData.EffectDataAsset);

	if (!WaterDataAsset)
		return false;
	
	EffectVFX = WaterDataAsset->EffectVFX;
	EffectElementType = WaterDataAsset->EffectElementType;
	BlendingEffectDataMap = WaterDataAsset->BlendingEffectDataMap;
	InitialDamageAmount = WaterDataAsset->InitialDamageAmount;
	TickDamageAmount = WaterDataAsset->TickDamageAmount;
	TicksCount = WaterDataAsset->TicksCount;
	TickAmount = WaterDataAsset->TickAmount;
	TickEffectVFX = WaterDataAsset->TickEffectVFX;
	SlowPercent = WaterDataAsset->SlowPercent;
	SlowTime = WaterDataAsset->SlowTime;
	StunTime = WaterDataAsset->StunTime;

	CurrTick = 0;
	return true;
}

bool UWaterEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);

	if (InAffectedObject.GetObject()->Implements<UMovable>())
	{
		if (APhysicsManager* PM = UNatureKeeperUtils::GetPhysicsManager(this))
		{
			PM->StartSlowActor(InAffectedObject.GetObject(), SlowPercent, SlowTime, StunTime);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Tickable Damageable Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), InitialDamageAmount);
	
	return true;
}
