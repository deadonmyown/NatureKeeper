// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/TickableDamageableEffect.h"

#include "Effects/EffectFactory.h"
#include "Effects/Data/TickableDamageableEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

bool UTickableDamageableEffect::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	UTickableDamageableEffectDataAsset* TickableDataAsset = Cast<UTickableDamageableEffectDataAsset>(InEffectDataAsset);

	if (!TickableDataAsset)
		return false;
	
	EffectVFX = TickableDataAsset->EffectVFX;
	EffectElementType = TickableDataAsset->EffectElementType;
	InitialDamageAmount = TickableDataAsset->InitialDamageAmount;
	TickDamageAmount = TickableDataAsset->TickDamageAmount;
	TicksCount = TickableDataAsset->TicksCount;
	TickAmount = TickableDataAsset->TickAmount;
	TickEffectVFX = TickableDataAsset->TickEffectVFX;

	CurrTick = 0;
	return true;
}

bool UTickableDamageableEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Tickable Damageable Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), InitialDamageAmount);
	
	return true;
}

bool UTickableDamageableEffect::CancelEffect()
{
	if (!AffectedObject.GetObject())
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);

		UE_LOG(LogTemp, Warning, TEXT("[TickableDamageableEffect] Affected Object Ptr is missing!"));
		OnFail.Broadcast(this);
		
		return false;
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	
	OnComplete.Broadcast(this);
	
	return true;
}

float UTickableDamageableEffect::GetEffectCompletionTime() const
{
	return TicksCount * TickAmount;
}

float UTickableDamageableEffect::GetEffectRemainingTime() const
{
	if (UWorld* World = GetWorld())
	{
		if (World->GetTimerManager().IsTimerActive(DamageTimerHandle))
		{
			return FMath::Max(0,TicksCount * TickAmount - World->GetTimerManager().GetTimerElapsed(DamageTimerHandle));
		}
	}
	return (TicksCount - CurrTick) * TickAmount;
}

void UTickableDamageableEffect::OnTickDamage()
{
	CurrTick++;

	TrySpawnVFX(TickEffectVFX);

	TryDamage(TickDamageAmount);

	if (CurrTick >= TicksCount)
	{
		CancelEffect();
	}
}
