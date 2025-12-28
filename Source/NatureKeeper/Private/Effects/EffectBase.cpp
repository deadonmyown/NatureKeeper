// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/EffectBase.h"

#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/EffectDataAsset.h"
#include "Interfaces/Affectable.h"

bool UEffectBase::InitEffect(UEffectDataAsset* InEffectDataAsset)
{
	EffectVFX = InEffectDataAsset->EffectVFX;
	EffectElementType = InEffectDataAsset->EffectElementType;
	
	return true;
}

bool UEffectBase::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!InAffectedObject.GetObject() || IAffectable::Execute_GetResistEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType)
		|| !IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this))
	{
		UE_LOG(LogTemp, Display, TEXT("[EffectBase] Failed to apply effect!"));
		OnFail.Broadcast(this);
		return false;
	}
	
	AffectedObject = InAffectedObject;
	
	return true;
}

bool UEffectBase::CancelEffect()
{
	if (!AffectedObject.GetObject())
	{
		UE_LOG(LogTemp, Warning, TEXT("[EffectBase] Affected Object Ptr is missing!"));
		OnFail.Broadcast(this);
		return false;
	}

	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);

	//Should I clear refs? If cancel effect it's not about cancel fully, but about pause effect? In this case we should keep references
	AffectedObject = nullptr;

	OnComplete.Broadcast(this);
	
	return true;
}

bool UEffectBase::TrySpawnVFX(UNiagaraSystem* InEffectVFX)
{
	if (!AffectedObject.GetObject() || !InEffectVFX)
		return false;

	if (USceneComponent* LocComponent = IAffectable::Execute_GetEffectLocation(AffectedObject.GetObject()))
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(InEffectVFX, LocComponent, FName(),
						LocComponent->GetComponentLocation(), LocComponent->GetComponentRotation(),
						FVector(1.f, 1.f, 1.f), EAttachLocation::Type::KeepWorldPosition,
						true, ENCPoolMethod::None, true, true);
		return true;
	}

	return false;
}
