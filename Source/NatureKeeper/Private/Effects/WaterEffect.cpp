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
	InitialDamageAmount = WaterDataAsset->InitialDamageAmount;
	TickDamageAmount = WaterDataAsset->TickDamageAmount;
	TicksCount = WaterDataAsset->TicksCount;
	TickAmount = WaterDataAsset->TickAmount;
	TickEffectVFX = WaterDataAsset->TickEffectVFX;
	SteamInitialDamageAmount = WaterDataAsset->SteamInitialDamageAmount;
	SteamEffectVFX = WaterDataAsset->SteamEffectVFX;
	return true;
}

bool UWaterEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!UDamageableBaseEffect::ApplyEffect(InAffectedObject))
		return false;

	TArray<UEffectBase*> ObjectEffects = IAffectable::Execute_GetEffects(InAffectedObject.GetObject());

	bool bHasOppositeEffect = false;
	for (int i = ObjectEffects.Num() - 1; i >= 0; i--)
	{
		if (ObjectEffects[i]->EffectElementType == EEffectElement::EE_Fire)
		{
			ObjectEffects[i]->CancelEffect();
			bHasOppositeEffect = true;
		}
	}

	if (bHasOppositeEffect)
	{
		TrySpawnVFX(SteamEffectVFX);

		TryDamage(SteamInitialDamageAmount);

		CancelEffect();

		UE_LOG(LogTemp, Display, TEXT("Water Effect (Steam): %d"), SteamInitialDamageAmount);
		
		return true;
	}

	TrySpawnVFX(EffectVFX);

	TryDamage(InitialDamageAmount);
		
	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("Water Effect: %d"), InitialDamageAmount);
	
	return true;
}
