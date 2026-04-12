// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/FreezeEffect.h"

#include "NatureKeeperUtils.h"
#include "Effects/Data/FreezeEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Freezable.h"
#include "Managers/PhysicsManager.h"

bool UFreezeEffect::InitEffect(const FEffectData& InEffectData)
{
	const UFreezeEffectDataAsset* FreezeEffectDataAsset = Cast<UFreezeEffectDataAsset>(InEffectData.EffectDataAsset);

	if (!FreezeEffectDataAsset)
		return false;
	
	EffectVFX = FreezeEffectDataAsset->EffectVFX;
	EffectElementType = FreezeEffectDataAsset->EffectElementType;
	BlendingEffectDataMap = FreezeEffectDataAsset->BlendingEffectDataMap;
	InitialDamageAmount = FreezeEffectDataAsset->InitialDamageAmount;
	TickDamageAmount = FreezeEffectDataAsset->TickDamageAmount;
	TicksCount = FreezeEffectDataAsset->TicksCount;
	TickAmount = FreezeEffectDataAsset->TickAmount;
	TickEffectVFX = FreezeEffectDataAsset->TickEffectVFX;

	CurrTick = 0;
	return true;
}

bool UFreezeEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);

	if (AffectedObject.GetObject()->Implements<UFreezable>())
	{
		if (APhysicsManager* PM = UNatureKeeperUtils::GetPhysicsManager(this))
		{
			PM->StartFreezeActor(AffectedObject.GetObject());
		}
	}

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Tickable Damageable Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), InitialDamageAmount);
	
	return true;
}

bool UFreezeEffect::CancelEffect()
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
			PM->StopFreezeActor(AffectedObject.GetObject());
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	
	OnComplete.Broadcast(this);
	
	return true;
}
