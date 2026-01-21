// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/TickableHealEffect.h"

#include "Effects/Data/TickableHealEffectDataAsset.h"
#include "Interfaces/Affectable.h"

bool UTickableHealEffect::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	UTickableHealEffectDataAsset* TickableDataAsset = Cast<UTickableHealEffectDataAsset>(InEffectDataAsset);

	if (!TickableDataAsset)
		return false;
	
	EffectVFX = TickableDataAsset->EffectVFX;
	EffectElementType = TickableDataAsset->EffectElementType;
	BlendingEffectDataAsset = InEffectDataAsset->BlendingEffectDataAsset;
	BlendingEffectElementType = InEffectDataAsset->BlendingEffectElementType;
	InitialHealAmount = TickableDataAsset->InitialHealAmount;
	TickHealAmount = TickableDataAsset->TickHealAmount;
	TicksCount = TickableDataAsset->TicksCount;
	TickAmount = TickableDataAsset->TickAmount;
	TickEffectVFX = TickableDataAsset->TickEffectVFX;

	CurrTick = 0;
	return true;
}

bool UTickableHealEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UHealBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryHeal(InitialHealAmount);

	GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UTickableHealEffect::OnTickHeal, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Tickable Heal Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), InitialHealAmount);
	
	return true;
}

bool UTickableHealEffect::CancelEffect()
{
	if (!AffectedObject.GetObject())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

		UE_LOG(LogTemp, Warning, TEXT("[TickableDamageableEffect] Affected Object Ptr is missing!"));
		OnFail.Broadcast(this);
		
		return false;
	}

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	
	OnComplete.Broadcast(this);
	
	return true;
}

float UTickableHealEffect::GetEffectCompletionTime() const
{
	return TicksCount * TickAmount;
}

float UTickableHealEffect::GetEffectRemainingTime() const
{
	if (UWorld* World = GetWorld())
	{
		if (World->GetTimerManager().IsTimerActive(HealTimerHandle))
		{
			return FMath::Max(0,TicksCount * TickAmount - World->GetTimerManager().GetTimerElapsed(HealTimerHandle));
		}
	}
	return (TicksCount - CurrTick) * TickAmount;
}

void UTickableHealEffect::OnTickHeal()
{
	CurrTick++;

	TrySpawnVFX(TickEffectVFX);

	TryHeal(TickHealAmount);

	if (CurrTick >= TicksCount)
	{
		CancelEffect();
	}
}
