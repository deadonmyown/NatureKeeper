// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/EffectBase.h"

#include "NatureKeeperUtils.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/EffectFactory.h"
#include "Effects/Data/EffectDataAsset.h"
#include "Interfaces/Affectable.h"

bool UEffectBase::InitEffect(const FEffectData& InEffectData)
{
	if (!InEffectData.EffectDataAsset)
		return false;
	
	EffectVFX = InEffectData.EffectDataAsset->EffectVFX;
	EffectElementType = InEffectData.EffectDataAsset->EffectElementType;
	BlendingEffectDataMap = InEffectData.EffectDataAsset->BlendingEffectDataMap;
	
	return true;
}

bool UEffectBase::ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!InAffectedObject.GetObject() || IAffectable::Execute_GetResistEffectElements(InAffectedObject.GetObject()).Contains(EffectElementType)
		|| !IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this))
	{
		UE_LOG(LogTemp, Display, TEXT("[EffectBase] Failed to apply effect!"));
		OnFail.Broadcast(this);
		return false;
	}

	AffectedObject = InAffectedObject;
	
	if (!BlendingEffectDataMap.IsEmpty())
	{
		TArray<UEffectBase*> ObjectEffects = IAffectable::Execute_GetEffects(InAffectedObject.GetObject());

		TArray<EEffectElement> OppositeEffectElements;
		for (int i = ObjectEffects.Num() - 1; i >= 0; i--)
		{
			if (BlendingEffectDataMap.Contains(ObjectEffects[i]->EffectElementType))
			{
				ObjectEffects[i]->CancelEffect();
				OppositeEffectElements.Add(ObjectEffects[i]->EffectElementType);
			}
		}

		if (!OppositeEffectElements.IsEmpty())
		{
			CancelEffect();
			for (int i = 0; i < OppositeEffectElements.Num(); i++)
			{
				if (UEffectBase* OppositeEffect = UNatureKeeperUtils::CreateEffect(InAffectedObject.GetObject(), BlendingEffectDataMap[OppositeEffectElements[i]]))
				{
					OppositeEffect->ApplyEffect(InAffectedObject);

					UE_LOG(LogTemp, Display, TEXT("Opposite Effect: %s"), *UEnum::GetDisplayValueAsText(OppositeEffectElements[i]).ToString());
				}
			}
			return false;
		}
	}
	
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
