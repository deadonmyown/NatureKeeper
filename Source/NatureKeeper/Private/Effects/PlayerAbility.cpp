// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/PlayerAbility.h"

#include "TargetSystem/TargetComponent.h"
#include "TargetSystem/TargetStrategy.h"

void UPlayerAbility::Target_Implementation(UTargetComponent* InTargetComponent)
{
	if (!CanCastAbility() || !InTargetComponent)
		return;
	
	if (!TargetStrategy)
	{
		TargetStrategy = InTargetComponent->DefaultTargetStrategy;
	}

	if (TargetStrategy->GetIsStarted())
	{
		TargetStrategy->CancelStrategy();
	}

	TargetStrategy->StartStrategy(this, InTargetComponent);
}

void UPlayerAbility::SetTargetStrategy(UTargetStrategy* NewTargetStrategy)
{
	if (!CanCastAbility() || !CanModifyAbility())
		return;
	
	if (TargetStrategy && TargetStrategy->GetIsStarted())
	{
		TargetStrategy->CancelStrategy();
	}
	
	TargetStrategy = NewTargetStrategy;
}

void UPlayerAbility::ClearTargetStrategy()
{
	if (!CanModifyAbility())
		return;
	
	if (TargetStrategy && TargetStrategy->GetIsStarted())
	{
		TargetStrategy->CancelStrategy();
	}
	
	TargetStrategy = nullptr;
}

bool UPlayerAbility::CanModifyAbility()
{
	if (TargetStrategy)
		return !TargetStrategy->GetIsTargeting();
	
	return true;
}

int32 UPlayerAbility::GetManaCost()
{
	int32 CurrManaCost = Super::GetManaCost();

	if (TargetStrategy)
		CurrManaCost += TargetStrategy->GetTargetStrategyManaCost();

	return CurrManaCost;
}
