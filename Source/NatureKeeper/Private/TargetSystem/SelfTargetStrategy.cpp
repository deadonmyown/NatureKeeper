// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/SelfTargetStrategy.h"

#include "NatureKeeperCharacter.h"
#include "Effects/Ability.h"
#include "Interfaces/Affectable.h"
#include "TargetSystem/TargetComponent.h"

bool USelfTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		PlayerController = Player->GetNatureKeeperController();
		
		Ability = InAbility;
		TargetComponent = InTargetComponent;

		TargetComponent->SetTargetStrategy(this);
		PlayerController->OnPlayerSecondaryClickStopped.AddDynamic(this, &USelfTargetStrategy::OnPlayerClickStopped);

		return true;
	}
	return false;
}

void USelfTargetStrategy::CancelStrategy()
{
	UTargetStrategy::CancelStrategy();
	
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &USelfTargetStrategy::OnPlayerClickStopped);
	
	if (TargetComponent->GetTargetStrategy() == this)
	{
		TargetComponent->ClearTargetStrategy();
	}

	PlayerController = nullptr;

	Ability = nullptr;
	TargetComponent = nullptr;
}

void USelfTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	if (TargetComponent->GetOwner()->Implements<UAffectable>() && Ability && Ability->TrySpendMana())
	{
		Ability->ApplyAbilityEffect(TargetComponent->GetOwner());
	}

	CancelStrategy();
}
