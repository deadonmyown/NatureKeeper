#include "TargetSystem/NPCsTargetStrategies/FlowTargetStrategyNPC.h"

#include "GameCollisionChannels.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/Ability.h"
#include "Interfaces/Affectable.h"
#include "Kismet/KismetMathLibrary.h"
#include "TargetSystem/TargetComponent.h"

bool UFlowTargetStrategyNPC::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
		return false;

	if (OverrideFlowUpdateTimeInSec >= 0.0f)
	{
		FlowUpdateTimeInSec = OverrideFlowUpdateTimeInSec;
	}
	else
	{
		FlowUpdateTimeInSec = Ability->GetAbilityCompletionTime();
		if (FlowUpdateTimeInSec <= 0.0f)
			FlowUpdateTimeInSec = DefaultFlowUpdateTimeInSec;
	}
	
	bIsTargeting = true;
	
	if (TargetStrategyVFX)
	{
		//Ensure that we don't have instances of ability vfx
		if (AbilityVFXComponent)
			AbilityVFXComponent->DestroyInstance();
	
		AbilityVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TargetStrategyVFX, InTargetComponent->GetOwner()->GetRootComponent(), FName(),
							InTargetComponent->GetOwner()->GetActorLocation(), InTargetComponent->GetOwner()->GetActorRotation(),
							FVector(1.f, 1.f, 1.f), EAttachLocation::Type::KeepWorldPosition,
							true, ENCPoolMethod::None, true, true);
	}

	return true;
}

void UFlowTargetStrategyNPC::UpdateStrategy(float DeltaTime)
{
	if (!Ability->CanCastAbility())
	{
		TargetComponent->CancelTargetStrategy();
		return;
	}
	
	FVector NPCDir = TargetComponent->GetOwner()->GetActorForwardVector();
	FRotator NPCRot = UKismetMathLibrary::MakeRotFromX(NPCDir);

	FVector StartTrace = TargetComponent->GetOwner()->GetActorLocation();
	FVector EndTrace = TargetComponent->GetOwner()->GetActorLocation() + NPCDir * TargetStrategyAffectDistance;
	
	const FName TraceTag("FlowTargetDebug");

	FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(TargetComponent->GetOwner());
	Params.TraceTag = TraceTag;
	Params.bTraceComplex = false;
	Params.bDebugQuery = true;

	GetWorld()->DebugDrawTraceTag = TraceTag;

	if (bHitSingleTarget)
	{
		FHitResult HitResult;

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			StartTrace,
			EndTrace,
			NPCRot.Quaternion(),
			CollisionChannels::ECC_Damageable,
			CapsuleShape,
			Params
		);

		if (HitResult.GetActor() && !CachedActors.Contains(HitResult.GetActor()) && HitResult.GetActor()->Implements<UAffectable>())
		{
			Ability->ApplyAbilityEffect(HitResult.GetActor(), FEffectHitData(HitResult.Normal, HitResult.Location, HitResult.GetComponent()));
			CachedActors.Add(FFlowUpdateData(HitResult.GetActor(), FlowUpdateTimeInSec));
		}
	}
	else
	{
		TArray<FHitResult> HitResults;

		bool bHit = GetWorld()->SweepMultiByChannel(
			HitResults,
			StartTrace,
			EndTrace,
			NPCRot.Quaternion(),
			CollisionChannels::ECC_Damageable,
			CapsuleShape,
			Params
		);
		
		for (int i = 0; i < HitResults.Num(); i++)
		{
			if (HitResults[i].GetActor() && !CachedActors.Contains(HitResults[i].GetActor()) && HitResults[i].GetActor()->Implements<UAffectable>())
			{
				Ability->ApplyAbilityEffect(HitResults[i].GetActor(), FEffectHitData(HitResults[i].Normal, HitResults[i].Location, HitResults[i].GetComponent()));
				CachedActors.Add(FFlowUpdateData(HitResults[i].GetActor(), FlowUpdateTimeInSec));
			}
		}
	}

	GetWorld()->DebugDrawTraceTag = NAME_None; 
	
	if (CurrentFlowCooldown > 0.0f)
	{
		CurrentFlowCooldown -= DeltaTime;

		for (int i = CachedActors.Num() - 1; i >= 0; i--)
		{
			CachedActors[i].RemainingTime -= DeltaTime;

			if (CachedActors[i].RemainingTime <= 0.001f)
				CachedActors.RemoveAt(i);
		}
		
		if (CurrentFlowCooldown <= 0.001f)
			CurrentFlowCooldown = 0.0f;
		return;
	}
	
	if (CurrentFlowCooldown == 0.0f)
	{
		Ability->TrySpendMana();
		
		CurrentFlowCooldown = FlowUpdateTimeInSec;
	}
}

void UFlowTargetStrategyNPC::CancelStrategy()
{
	if (AbilityVFXComponent)
		AbilityVFXComponent->DestroyInstance();

	CurrentFlowCooldown = 0.0f;
	CachedActors.Empty();

	UTargetStrategy::CancelStrategy();
}