// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/FocusTargetStrategy.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "Effects/Ability.h"
#include "TargetSystem/TargetComponent.h"

bool UFocusTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();

		bIsTargeting = true;
		Ability = InAbility;
		TargetComponent = InTargetComponent;

		TargetComponent->SetTargetStrategy(this);
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
	UTargetStrategy::CancelStrategy();
	
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UFocusTargetStrategy::OnPlayerClickStopped);
	
	if (TargetComponent->GetTargetStrategy() == this)
	{
		TargetComponent->ClearTargetStrategy();
	}

	FocusComponent = nullptr;
	PlayerController = nullptr;

	bIsTargeting = false;
	Ability = nullptr;
	TargetComponent = nullptr;
}

void UFocusTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	FocusComponent->UpdateTrace();

	if (FocusComponent->CursorFocusedActor && FocusComponent->CursorFocusedActor->Implements<UAffectable>()
		&& Ability && Ability->TrySpendMana())
	{
		Ability->ApplyAbilityEffect(FocusComponent->CursorFocusedActor);
	}
	
	CancelStrategy();
}
