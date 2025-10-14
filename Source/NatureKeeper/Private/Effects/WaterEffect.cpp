// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/WaterEffect.h"

#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"

bool UWaterEffect::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!InAffectedObject.GetObject() || !EffectFactory || !InAffectedObject.GetObject()->Implements<UDamageable>())
		return false;

	if (IAffectable::Execute_GetResistEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType))
		return false;
	
	AffectedObject = InAffectedObject;
	EffectFactory->AddEffect(this);
	IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this);

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
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SteamEffectVFX,
					IAffectable::Execute_GetEffectLocation(InAffectedObject.GetObject()),
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);

		IDamageable::Execute_TakeDamage(InAffectedObject.GetObject(), SteamInitialDamageAmount);

		CancelEffect();
		return true;
	}

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
