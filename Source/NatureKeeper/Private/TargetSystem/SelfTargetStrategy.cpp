// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/SelfTargetStrategy.h"

#include "NatureKeeperCharacter.h"
#include "Effects/PlayerAbility.h"
#include "Interfaces/Affectable.h"
#include "TargetSystem/TargetComponent.h"

bool USelfTargetStrategy::StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		PlayerController = Player->GetNatureKeeperController();
		
		PlayerController->OnPlayerThirdClickStopped.AddDynamic(this, &USelfTargetStrategy::OnPlayerClickStopped);

		return true;
	}
	return false;
}

void USelfTargetStrategy::CancelStrategy(bool bClearAbility)
{
	PlayerController->OnPlayerThirdClickStopped.RemoveDynamic(this, &USelfTargetStrategy::OnPlayerClickStopped);

	PlayerController = nullptr;
	
	UTargetStrategy::CancelStrategy(bClearAbility);
}

void USelfTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	if (TargetComponent->GetOwner()->Implements<UAffectable>() && Ability && Ability->TrySpendMana())
	{
		Ability->ApplyAbilityEffect(TargetComponent->GetOwner());
	}

	CancelStrategy(true);
}
