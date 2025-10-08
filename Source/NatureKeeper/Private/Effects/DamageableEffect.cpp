// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/DamageableEffect.h"

#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/DamageableEffectDataAsset.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

bool UDamageableEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!InAffectedObject.GetObject() || !EffectFactory || !InAffectedObject.GetObject()->Implements<UDamageable>())
		return false;
	
	
	AffectedObject = InAffectedObject;
	EffectFactory->AddEffect(this);
	IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, EffectDataAsset->EffectVFX,
					IAffectable::Execute_GetEffectLocation(InAffectedObject.GetObject()),
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);
	
	IDamageable::Execute_TakeDamage(InAffectedObject.GetObject(), EffectDataAsset->DamageAmount);

	UE_LOG(LogTemp, Display, TEXT("AffectedObject: %s"), *InAffectedObject.GetObject()->GetName());
	UE_LOG(LogTemp, Display, TEXT("Effect factory: %s"), *EffectFactory->GetName());

	//Immediately cancel because this is base effect
	CancelEffect();
	
	return true;
}

bool UDamageableEffect::CancelEffect()
{
	return Super::CancelEffect();
}
