// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/EffectBase.h"

#include "Interfaces/Affectable.h"

bool UEffectBase::ApplyEffect(TArray<TScriptInterface<UAffectable>> InAffectedObjects)
{
	if (InAffectedObjects.IsEmpty())
		return false;
	
	for (int i = 0; i < InAffectedObjects.Num(); i++)
	{
		if (InAffectedObjects[i].GetObject() && !AffectedObjects.Contains(InAffectedObjects[i]))
		{
			AffectedObjects.Add(InAffectedObjects[i]);
			IAffectable::Execute_RegisterEffect(InAffectedObjects[i].GetObject(), this);

			UE_LOG(LogTemp, Display, TEXT("AffectedObject: %s"), *InAffectedObjects[i].GetObject()->GetName());
		}
	}

	if (AffectedObjects.IsEmpty())
		return false;

	//Immediately cancel because this is base effect
	CancelEffect();

	UE_LOG(LogTemp, Display, TEXT("Effect: %s"), *GetName());
	
	return true;
}

bool UEffectBase::CancelEffectSingle(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!AffectedObjects.Contains(InAffectedObject))
		return false;
	
	IAffectable::Execute_UnregisterEffect(InAffectedObject.GetObject(), this);
	AffectedObjects.Remove(InAffectedObject);
	
	OnComplete.Broadcast(InAffectedObject);
	return true;
}

bool UEffectBase::CancelEffect()
{
	if (AffectedObjects.IsEmpty())
		return false;
	
	for (int i = 0; i < AffectedObjects.Num(); i++)
	{
		IAffectable::Execute_UnregisterEffect(AffectedObjects[i].GetObject(), this);
		OnComplete.Broadcast(AffectedObjects[i]);
	}
	
	AffectedObjects.Empty();
	
	return true;
}

TArray<TScriptInterface<UAffectable>> UEffectBase::GetAffectedObjects()
{
	return AffectedObjects;
}