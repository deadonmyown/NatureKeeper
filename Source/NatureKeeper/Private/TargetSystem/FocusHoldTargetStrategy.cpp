// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/FocusHoldTargetStrategy.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperPlayerController.h"
#include "Effects/Ability.h"
#include "Effects/Data/AbilityDataAsset.h"
#include "Interfaces/Affectable.h"
#include "TargetSystem/TargetComponent.h"

bool UFocusHoldTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();
		
		bIsTargeting = true;
		bFocusStart = false;
		Ability = InAbility;
		TargetComponent = InTargetComponent;

		AbilityDistance = Ability->GetAbilityDataAsset()->AbilityAffectDistance;
		if (OverrideFocusUpdateTimeInSec >= 0.0f)
		{
			FocusUpdateTimeInSec = OverrideFocusUpdateTimeInSec;
		}
		else
		{
			FocusUpdateTimeInSec = Ability->GetAbilityCompletionTime();
		}

		TargetComponent->SetTargetStrategy(this);
		PlayerController->OnPlayerSecondaryClickStarted.AddDynamic(this, &UFocusHoldTargetStrategy::OnPlayerClickStarted);
		PlayerController->OnPlayerSecondaryClickStopped.AddDynamic(this, &UFocusHoldTargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UFocusHoldTargetStrategy::UpdateStrategy(float DeltaTime)
{
	if (!Ability->CanCastAbility())
	{
		CancelStrategy();
		return;
	}

	if (CurrentFocusCooldown > 0.0f)
	{
		CurrentFocusCooldown -= DeltaTime;
		
		if (CurrentFocusCooldown < 0.0f)
			CurrentFocusCooldown = 0.0f;
		return;
	}

	if (bFocusStart && CurrentFocusCooldown == 0.0f)
	{
		FocusComponent->UpdateTrace();

		if (FocusComponent->FocusedActor && FocusComponent->FocusedActor->Implements<UAffectable>()
			&& Ability && Ability->TrySpendMana())
		{
			Ability->ApplyAbilityEffect(FocusComponent->FocusedActor);

			CurrentFocusCooldown = FocusUpdateTimeInSec;
		}
	}
}

void UFocusHoldTargetStrategy::CancelStrategy()
{
	UTargetStrategy::CancelStrategy();
	
	PlayerController->OnPlayerSecondaryClickStarted.RemoveDynamic(this, &UFocusHoldTargetStrategy::OnPlayerClickStarted);
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UFocusHoldTargetStrategy::OnPlayerClickStopped);

	bFocusStart = false;
	
	if (TargetComponent->GetTargetStrategy() == this)
	{
		TargetComponent->ClearTargetStrategy();
	}

	if (bCancelAbility)
	{
		Ability->CancelAbilityEffect();
	}

	FocusComponent = nullptr;
	PlayerController = nullptr;

	bIsTargeting = false;
	Ability = nullptr;
	TargetComponent = nullptr;
}

void UFocusHoldTargetStrategy::OnPlayerClickStarted()
{
	bFocusStart = true;
}

void UFocusHoldTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	CancelStrategy();
}
