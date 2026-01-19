// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/FocusTargetStrategy.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "Effects/PlayerAbility.h"
#include "TargetSystem/TargetComponent.h"

bool UFocusTargetStrategy::StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();

		PlayerController->OnPlayerSecondaryClickStopped.AddDynamic(this, &UFocusTargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UFocusTargetStrategy::UpdateStrategy(float DeltaTime)
{
	
}

void UFocusTargetStrategy::CancelStrategy(bool bClearAbility)
{
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UFocusTargetStrategy::OnPlayerClickStopped);

	FocusComponent = nullptr;
	PlayerController = nullptr;

	UTargetStrategy::CancelStrategy(bClearAbility);
}

void UFocusTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	FocusComponent->UpdateTrace();

	if (FocusComponent->CursorFocusedActor && FocusComponent->CursorFocusedActor->Implements<UAffectable>()
		&& Ability && Ability->TrySpendMana())
	{
		Ability->ApplyAbilityEffect(FocusComponent->CursorFocusedActor);
	}
	
	CancelStrategy(true);
}
