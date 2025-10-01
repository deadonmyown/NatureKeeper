// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/SelfTargetStrategy.h"

#include "Effects/Ability.h"
#include "Interfaces/Affectable.h"
#include "TargetSystem/TargetComponent.h"

void USelfTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	Ability = InAbility;
	TargetComponent = InTargetComponent;

	if (TargetComponent->GetOwner()->Implements<UAffectable>())
	{
		Ability->ApplyAbilityEffect(TargetComponent->GetOwner());
	}
}
