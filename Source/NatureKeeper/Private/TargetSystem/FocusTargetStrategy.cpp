// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/FocusTargetStrategy.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "Effects/Ability.h"
#include "TargetSystem/TargetComponent.h"

void UFocusTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();

		bIsTargeting = true;
		Ability = InAbility;
		TargetComponent = InTargetComponent;

		TargetComponent->SetTargetStrategy(this);
		PlayerController->OnPlayerClickStopped.AddDynamic(this, &UFocusTargetStrategy::OnPlayerClickStopped);
	}
}

void UFocusTargetStrategy::UpdateStrategy()
{
	
}

void UFocusTargetStrategy::CancelStrategy()
{
	PlayerController->OnPlayerClickStopped.RemoveDynamic(this, &UFocusTargetStrategy::OnPlayerClickStopped);
	
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

void UFocusTargetStrategy::OnPlayerClickStopped()
{
	if (Ability)
	{
		FocusComponent->UpdateTrace();

		if (FocusComponent->FocusedActor && FocusComponent->FocusedActor->Implements<UAffectable>())
		{
			Ability->ApplyAbilityEffect(FocusComponent->FocusedActor);
			CancelStrategy();
		}
	}
}
