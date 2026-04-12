// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/SelfTargetStrategy.h"

#include "NatureKeeperCharacter.h"
#include "Effects/Ability.h"
#include "Interfaces/Affectable.h"
#include "TargetSystem/ProjectileTargetStrategy.h"
#include "TargetSystem/TargetComponent.h"

bool USelfTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		PlayerController = Player->GetNatureKeeperController();

		PlayerController->OnPlayerThirdClickStarted.AddDynamic(this, &USelfTargetStrategy::OnPlayerClickStarted);
		PlayerController->OnPlayerThirdClickStopped.AddDynamic(this, &USelfTargetStrategy::OnPlayerClickStopped);

		return true;
	}
	return false;
}

void USelfTargetStrategy::CancelStrategy()
{
	PlayerController->OnPlayerThirdClickStarted.RemoveDynamic(this, &USelfTargetStrategy::OnPlayerClickStarted);
	PlayerController->OnPlayerThirdClickStopped.RemoveDynamic(this, &USelfTargetStrategy::OnPlayerClickStopped);

	PlayerController = nullptr;
	
	UTargetStrategy::CancelStrategy();
}

void USelfTargetStrategy::OnPlayerClickStarted()
{
	bIsTargeting = true;
}

void USelfTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	if (TargetComponent->GetOwner()->Implements<UAffectable>() && Ability && Ability->TrySpendMana())
	{
		const FEffectHitData& HitData = FEffectHitData(TargetComponent->GetOwner()->GetTransform().InverseTransformVector(HitNormal));
		Ability->ApplyAbilityEffect(TargetComponent->GetOwner(), HitData);
	}

	TargetComponent->CancelTargetStrategy();
}
