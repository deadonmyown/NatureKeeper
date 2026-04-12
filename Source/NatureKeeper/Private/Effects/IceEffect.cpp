// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/IceEffect.h"

#include "NatureKeeperUtils.h"
#include "Effects/Data/IceEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Freezable.h"
#include "Managers/PhysicsManager.h"

bool UIceEffect::InitEffect(const FEffectData& InEffectData)
{
	const UIceEffectDataAsset* IceEffectDataAsset = Cast<UIceEffectDataAsset>(InEffectData.EffectDataAsset);

	if (!IceEffectDataAsset)
		return false;
	
	EffectVFX = IceEffectDataAsset->EffectVFX;
	EffectElementType = IceEffectDataAsset->EffectElementType;
	BlendingEffectDataMap = IceEffectDataAsset->BlendingEffectDataMap;
	InitialDamageAmount = IceEffectDataAsset->InitialDamageAmount;
	TickDamageAmount = IceEffectDataAsset->TickDamageAmount;
	TicksCount = IceEffectDataAsset->TicksCount;
	TickAmount = IceEffectDataAsset->TickAmount;
	TickEffectVFX = IceEffectDataAsset->TickEffectVFX;
	IceSlowPercent = IceEffectDataAsset->IceSlowPercent;

	CurrTick = 0;
	return true;
}

bool UIceEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);

	if (AffectedObject.GetObject()->Implements<UFreezable>())
	{
		if (APhysicsManager* PM = UNatureKeeperUtils::GetPhysicsManager(this))
		{
			PM->StartIceSlowActor(AffectedObject.GetObject(), IceSlowPercent);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Tickable Damageable Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), InitialDamageAmount);
	
	return true;
}

bool UIceEffect::CancelEffect()
{
	if (!AffectedObject.GetObject())
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);

		UE_LOG(LogTemp, Warning, TEXT("[TickableDamageableEffect] Affected Object Ptr is missing!"));
		OnFail.Broadcast(this);
		
		return false;
	}

	if (AffectedObject.GetObject()->Implements<UFreezable>())
	{
		if (APhysicsManager* PM = UNatureKeeperUtils::GetPhysicsManager(this))
		{
			PM->StopIceSlowActor(AffectedObject.GetObject(), IceSlowPercent);
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	
	OnComplete.Broadcast(this);
	
	return true;
}
