#include "TargetSystem/FlowTargetStrategy.h"

#include "FocusComponent.h"
#include "GameCollisionChannels.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperGameMode.h"
#include "NiagaraFunctionLibrary.h"
#include "TargetSystem/TargetComponent.h"
#include "NiagaraComponent.h"
#include "Effects/Ability.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"



bool UFlowTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();
		MuzzleComponent = FocusComponent->GetPlayerMuzzleComponent();

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

		PlayerController->OnPlayerMainClickStarted.AddDynamic(this, &UFlowTargetStrategy::OnPlayerClickStarted);
		PlayerController->OnPlayerMainClickStopped.AddDynamic(this, &UFlowTargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UFlowTargetStrategy::UpdateStrategy(float DeltaTime)
{
	if (!Ability->CanCastAbility())
	{
		TargetComponent->CancelTargetStrategy();
		return;
	}
	
	FVector PlayerDir;
	FocusComponent->GetPlayerLookAtNormalized(PlayerDir);
	FRotator PlayerRot = UKismetMathLibrary::MakeRotFromX(PlayerDir);

	FVector StartTrace = MuzzleComponent->GetComponentLocation();
	FVector EndTrace = MuzzleComponent->GetComponentLocation() + PlayerDir * TargetStrategyAffectDistance;
	
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
			PlayerRot.Quaternion(),
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
			PlayerRot.Quaternion(),
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

void UFlowTargetStrategy::CancelStrategy()
{
	PlayerController->OnPlayerMainClickStarted.RemoveDynamic(this, &UFlowTargetStrategy::OnPlayerClickStarted);
	PlayerController->OnPlayerMainClickStopped.RemoveDynamic(this, &UFlowTargetStrategy::OnPlayerClickStopped);
	
	if (AbilityVFXComponent)
		AbilityVFXComponent->DestroyInstance();

	CurrentFlowCooldown = 0.0f;
	CachedActors.Empty();

	FocusComponent = nullptr;
	PlayerController = nullptr;
	MuzzleComponent = nullptr;

	UTargetStrategy::CancelStrategy();
}

void UFlowTargetStrategy::OnPlayerClickStarted()
{
	bIsTargeting = true;
	
	if (TargetStrategyVFX)
	{
		FVector VFXLoc;
		FocusComponent->GetPlayerLookAtNormalizedLocation(VFXLoc);
		//Ensure that we don't have instances of ability vfx
		if (AbilityVFXComponent)
			AbilityVFXComponent->DestroyInstance();
	
		AbilityVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(TargetStrategyVFX, MuzzleComponent, FName(),
							MuzzleComponent->GetComponentLocation(), MuzzleComponent->GetComponentRotation(),
							FVector(1.f, 1.f, 1.f), EAttachLocation::Type::KeepWorldPosition,
							true, ENCPoolMethod::None, true, true);
	}
}

void UFlowTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	TargetComponent->CancelTargetStrategy();
}
