// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/EffectBase.h"

bool UEffectBase::ApplyEffect_Implementation(AActor* InAffectedActor)
{
	if (!InAffectedActor)
		return false;

	AffectedActor = InAffectedActor;
	return true;
}

bool UEffectBase::CancelEffect_Implementation()
{
	AffectedActor = nullptr;
	return true;
}

AActor* UEffectBase::GetAffectedActor_Implementation()
{
	return AffectedActor;
}
