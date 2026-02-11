// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/PlayerAbility.h"

#include "TargetSystem/TargetComponent.h"
#include "TargetSystem/TargetStrategy.h"

void UPlayerAbility::Target_Implementation()
{
	if (!CanCastAbility() || !TargetComponent)
		return;

	if (!TargetStrategy)
	{
		TargetStrategy = TargetComponent->DefaultTargetStrategy;
	}

	TargetComponent->SetTargetStrategy(TargetStrategy);
	TargetComponent->StartTargetStrategy(this);
}

void UPlayerAbility::InitTargetComponent(UTargetComponent* InTargetComponent)
{
	ClearTargetStrategy();
	
	TargetComponent = InTargetComponent;
}

void UPlayerAbility::SetTargetStrategy(UTargetStrategy* NewTargetStrategy)
{
	if (!CanModifyAbility())
		return;

	TargetStrategy = NewTargetStrategy;
}

void UPlayerAbility::ClearTargetStrategy()
{
	if (!TargetComponent || !CanModifyAbility())
		return;

	TargetStrategy = nullptr;
	TargetComponent->CancelTargetStrategy();
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
