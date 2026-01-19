// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/FocusHoldTargetStrategy.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperPlayerController.h"
#include "Effects/PlayerAbility.h"
#include "Interfaces/Affectable.h"
#include "TargetSystem/TargetComponent.h"

bool UFocusHoldTargetStrategy::StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();

		if (OverrideFocusUpdateTimeInSec >= 0.0f)
		{
			FocusUpdateTimeInSec = OverrideFocusUpdateTimeInSec;
		}
		else
		{
			FocusUpdateTimeInSec = Ability->GetAbilityCompletionTime();
		}

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
		CancelStrategy(true);
		return;
	}

	FVector TraceLocation = ITarget::Execute_GetTargetLocation(FocusComponent);

	if (TargetStrategyAffectDistance > 0.0f && FVector::Distance(FocusComponent->GetOwner()->GetActorLocation(), TraceLocation) > TargetStrategyAffectDistance)
	{
		CancelStrategy(true);
		return;
	}

	if (CurrentFocusCooldown > 0.0f)
	{
		CurrentFocusCooldown -= DeltaTime;
		
		if (CurrentFocusCooldown < 0.0f)
			CurrentFocusCooldown = 0.0f;
		return;
	}

	if (CurrentFocusCooldown == 0.0f)
	{
		if (CachedFocusActor)
		{
			if (Ability && Ability->TrySpendMana())
			{
				Ability->ApplyAbilityEffect(CachedFocusActor);

				CurrentFocusCooldown = FocusUpdateTimeInSec;
			}
		}
		else
		{
			FocusComponent->UpdateTrace();

			if (FocusComponent->CursorFocusedActor && FocusComponent->CursorFocusedActor->Implements<UAffectable>()
				&& Ability && Ability->TrySpendMana())
			{
				CachedFocusActor = FocusComponent->CursorFocusedActor;
				Ability->ApplyAbilityEffect(FocusComponent->CursorFocusedActor);

				CurrentFocusCooldown = FocusUpdateTimeInSec;
			}
		}
	}
}

void UFocusHoldTargetStrategy::CancelStrategy(bool bClearAbility)
{
	PlayerController->OnPlayerSecondaryClickStarted.RemoveDynamic(this, &UFocusHoldTargetStrategy::OnPlayerClickStarted);
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UFocusHoldTargetStrategy::OnPlayerClickStopped);

	/*if (bCancelAbility)
	{
		Ability->CancelAbilityEffect();
	}*/

	FocusComponent = nullptr;
	PlayerController = nullptr;

	CachedFocusActor = nullptr;
	UTargetStrategy::CancelStrategy(bClearAbility);
}

void UFocusHoldTargetStrategy::OnPlayerClickStarted()
{
	bIsTargeting = true;
}

void UFocusHoldTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	CancelStrategy(true);
}
