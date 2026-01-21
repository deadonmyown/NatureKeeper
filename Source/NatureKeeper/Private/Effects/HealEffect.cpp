// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/HealEffect.h"

#include "Effects/Data/HealEffectDataAsset.h"

bool UHealEffect::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	UHealEffectDataAsset* HealDataAsset = Cast<UHealEffectDataAsset>(InEffectDataAsset);

	if (!HealDataAsset)
		return false;
	
	EffectVFX = HealDataAsset->EffectVFX;
	EffectElementType = HealDataAsset->EffectElementType;
	BlendingEffectDataAsset = InEffectDataAsset->BlendingEffectDataAsset;
	BlendingEffectElementType = InEffectDataAsset->BlendingEffectElementType;
	HealAmount = HealDataAsset->HealAmount;
	return true;
}

bool UHealEffect::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!UHealBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TrySpawnVFX(EffectVFX);

	TryHeal(HealAmount);

	UE_LOG(LogTemp, Display, TEXT("Heal Effect(%s): %d"), *UEnum::GetDisplayValueAsText(EffectElementType).ToString(), HealAmount);

	//Immediately cancel because this is one shot effect
	CancelEffect();
	
	return true;
}
