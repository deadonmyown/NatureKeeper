// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/AOETargetStrategy.h"

#include "FocusComponent.h"
#include "GameCollisionChannels.h"
#include "NatureKeeperCharacter.h"
#include "Effects/PlayerAbility.h"
#include "TargetSystem/TargetComponent.h"

bool UAOETargetStrategy::StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();

		bIsTargeting = true;
		
		PlayerController->OnPlayerMainClickStopped.AddDynamic(this, &UAOETargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UAOETargetStrategy::CancelStrategy(bool bClearAbility)
{
	PlayerController->OnPlayerMainClickStopped.RemoveDynamic(this, &UAOETargetStrategy::OnPlayerClickStopped);

	FocusComponent = nullptr;
	PlayerController = nullptr;
	
	UTargetStrategy::CancelStrategy(bClearAbility);
}

void UAOETargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	if (!Ability || !Ability->TrySpendMana())
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
	
	TArray<FHitResult> HitResults;

	const FName TraceTag("AOETargetDebug");

	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(AOERadius, AOEHalfHeight);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(TargetComponent->GetOwner());
	Params.TraceTag = TraceTag;
	Params.bTraceComplex = false;
	Params.bDebugQuery = true;

	GetWorld()->DebugDrawTraceTag = TraceTag;

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		TraceLocation,
		TraceLocation,
		FQuat::Identity,
		CollisionChannels::ECC_Damageable,
		CapsuleShape,
		Params
	);

	GetWorld()->DebugDrawTraceTag = NAME_None; 
		
	for (int i = 0; i < HitResults.Num(); i++)
	{
		if (HitResults[i].GetActor() && HitResults[i].GetActor()->Implements<UAffectable>())
		{
			Ability->ApplyAbilityEffect(HitResults[i].GetActor());
		}
	}

	CancelStrategy(true);
}
