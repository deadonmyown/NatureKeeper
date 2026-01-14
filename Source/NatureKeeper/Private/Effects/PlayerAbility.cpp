// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/PlayerAbility.h"

#include "TargetSystem/TargetStrategy.h"

void UPlayerAbility::Target_Implementation(UTargetComponent* InTargetComponent)
{
	if (!CanCastAbility() || !InTargetComponent)
		return;

	TargetStrategy->StartStrategy(this, InTargetComponent);
}
