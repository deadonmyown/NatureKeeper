// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/EffectBase.h"

#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"

bool UEffectBase::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!InAffectedObject.GetObject() || !EffectFactory)
		return false;

	if (IAffectable::Execute_GetResistEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType))
		return false;
	
	if (!IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this))
		return false;
	
	AffectedObject = InAffectedObject;
	EffectFactory->AddEffect(this);
	
	return true;
}

bool UEffectBase::CancelEffect()
{
	if (!AffectedObject.GetObject() || !EffectFactory)
	{
		OnComplete.Broadcast();
		return false;
	}

	EffectFactory->RemoveEffect(this);
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	EffectFactory = nullptr;

	OnComplete.Broadcast();
	
	return true;
}

bool UEffectBase::TrySpawnVFX(UNiagaraSystem* InEffectVFX)
{
	if (!AffectedObject.GetObject() || !InEffectVFX)
		return false;

	if (USceneComponent* LocComponent = IAffectable::Execute_GetEffectLocation(AffectedObject.GetObject()))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, InEffectVFX,
						LocComponent->GetComponentLocation(), LocComponent->GetComponentRotation(),
						FVector(1.f, 1.f, 1.f),
						true, true, ENCPoolMethod::None, true);
		return true;
	}

	return false;
}
