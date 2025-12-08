// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/TickableDamageableEffect.h"

#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

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
	if (!AffectedObject.GetObject() || !EffectFactory)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);

		OnComplete.Broadcast();
		
		return false;
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	EffectFactory->RemoveEffect(this);
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	EffectFactory = nullptr;
	
	OnComplete.Broadcast();
	
	return true;
}

void UTickableDamageableEffect::OnTickDamage()
{
	TicksCount--;

	TrySpawnVFX(TickEffectVFX);

	TryDamage(TickDamageAmount);

	if (TicksCount <= 0)
	{
		CancelEffect();
	}
}
