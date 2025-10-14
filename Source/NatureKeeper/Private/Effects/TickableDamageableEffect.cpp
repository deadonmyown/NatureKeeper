// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/TickableDamageableEffect.h"

#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

bool UTickableDamageableEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!InAffectedObject.GetObject() || !EffectFactory || !InAffectedObject.GetObject()->Implements<UDamageable>())
		return false;

	if (IAffectable::Execute_GetResistEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType))
		return false;
	
	AffectedObject = InAffectedObject;
	EffectFactory->AddEffect(this);
	IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this);
	

	if (InitialDamageAmount > 0)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EffectVFX,
					IAffectable::Execute_GetEffectLocation(InAffectedObject.GetObject()),
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);
		
		IDamageable::Execute_TakeDamage(InAffectedObject.GetObject(), InitialDamageAmount);
	}

	GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &UTickableDamageableEffect::OnTickDamage, TickAmount, true);

	UE_LOG(LogTemp, Display, TEXT("AffectedObject: %s"), *InAffectedObject.GetObject()->GetName());
	UE_LOG(LogTemp, Display, TEXT("Effect factory: %s"), *EffectFactory->GetName());
	
	return true;
}

bool UTickableDamageableEffect::CancelEffect()
{
	if (!AffectedObject.GetObject() || !EffectFactory)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
		return false;
	}

	GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	
	EffectFactory->RemoveEffect(this);
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	EffectFactory = nullptr;
	
	return true;
}

void UTickableDamageableEffect::OnTickDamage()
{
	TicksCount--;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TickEffectVFX,
					IAffectable::Execute_GetEffectLocation(AffectedObject.GetObject()),
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);
		
	IDamageable::Execute_TakeDamage(AffectedObject.GetObject(), TickDamageAmount);

	if (TicksCount <= 0)
	{
		CancelEffect();
	}
}
