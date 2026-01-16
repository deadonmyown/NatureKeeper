// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/AOETargetStrategy.h"

#include "FocusComponent.h"
#include "GameCollisionChannels.h"
#include "NatureKeeperCharacter.h"
#include "Effects/Ability.h"
#include "Effects/Data/AbilityDataAsset.h"
#include "TargetSystem/TargetComponent.h"

bool UAOETargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
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

		AbilityDistance = Ability->GetAbilityDataAsset()->AbilityAffectDistance;

		TargetComponent->SetTargetStrategy(this);
		PlayerController->OnPlayerSecondaryClickStopped.AddDynamic(this, &UAOETargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UAOETargetStrategy::CancelStrategy()
{
	UTargetStrategy::CancelStrategy();
	
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UAOETargetStrategy::OnPlayerClickStopped);
	
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

void UAOETargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	if (!Ability && !Ability->TrySpendMana())
	{
		CancelStrategy();
		return;
	}

	FVector TraceLocation = ITarget::Execute_GetTargetLocation(FocusComponent);
	//TraceLocation.Z -= AOEHalfHeight;

	if (AbilityDistance > 0.0f && FVector::Distance(FocusComponent->GetOwner()->GetActorLocation(), TraceLocation) > AbilityDistance)
		return;
	
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

	CancelStrategy();
}
