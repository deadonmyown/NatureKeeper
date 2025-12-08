// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/WaterEffect.h"

#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

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
