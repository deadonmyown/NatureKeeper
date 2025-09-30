// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/EffectBase.h"

#include "Effects/EffectFactory.h"
#include "Interfaces/Affectable.h"

bool UEffectBase::ApplyEffect(TScriptInterface<UAffectable> InAffectedObject)
{
	if (!InAffectedObject.GetObject() || !EffectFactory)
		return false;
	
	
	AffectedObject = InAffectedObject;
	EffectFactory->AddEffect(this);
	IAffectable::Execute_RegisterEffect(InAffectedObject.GetObject(), this);

	UE_LOG(LogTemp, Display, TEXT("AffectedObject: %s"), *InAffectedObject.GetObject()->GetName());
	UE_LOG(LogTemp, Display, TEXT("Effect factory: %s"), *EffectFactory->GetName());

	//Immediately cancel because this is base effect
	CancelEffect();

	
	return true;
}

bool UEffectBase::CancelEffect()
{
	if (!AffectedObject.GetObject() || !EffectFactory)
		return false;

	EffectFactory->RemoveEffect(this);
	IAffectable::Execute_UnregisterEffect(AffectedObject.GetObject(), this);
		
	AffectedObject = nullptr;
	EffectFactory = nullptr;
	
	return true;
}