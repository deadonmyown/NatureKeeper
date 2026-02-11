// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/FocusTargetStrategy.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "Effects/Ability.h"
#include "TargetSystem/ProjectileTargetStrategy.h"
#include "TargetSystem/TargetComponent.h"

bool UFocusTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();

		PlayerController->OnPlayerSecondaryClickStarted.AddDynamic(this, &UFocusTargetStrategy::OnPlayerClickStarted);
		PlayerController->OnPlayerSecondaryClickStopped.AddDynamic(this, &UFocusTargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UFocusTargetStrategy::UpdateStrategy(float DeltaTime)
{
	
}

void UFocusTargetStrategy::CancelStrategy()
{
	PlayerController->OnPlayerSecondaryClickStarted.RemoveDynamic(this, &UFocusTargetStrategy::OnPlayerClickStarted);
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UFocusTargetStrategy::OnPlayerClickStopped);

	FocusComponent = nullptr;
	PlayerController = nullptr;

	UTargetStrategy::CancelStrategy();
}

void UFocusTargetStrategy::OnPlayerClickStarted()
{
	bIsTargeting = true;
}

void UFocusTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	FocusComponent->UpdateTrace();

	if (FocusComponent->CursorFocusedActor && FocusComponent->CursorFocusedActor->Implements<UAffectable>()
		&& Ability && Ability->TrySpendMana())
	{
		Ability->ApplyAbilityEffect(FocusComponent->CursorFocusedActor);
	}
	
	TargetComponent->CancelTargetStrategy();
}
