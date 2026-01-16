// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/FlowTargetStrategy.h"

#include "FocusComponent.h"
#include "GameCollisionChannels.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperGameMode.h"
#include "NiagaraFunctionLibrary.h"
#include "Effects/Ability.h"
#include "Effects/Data/AbilityDataAsset.h"
#include "TargetSystem/TargetComponent.h"
#include "NiagaraComponent.h"
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

		bIsTargeting = true;
		bFlowStart = false;
		Ability = InAbility;
		TargetComponent = InTargetComponent;

		AbilityDistance = Ability->GetAbilityDataAsset()->AbilityAffectDistance;
		if (OverrideFlowUpdateTimeInSec >= 0.0f)
		{
			FlowUpdateTimeInSec = OverrideFlowUpdateTimeInSec;
		}
		else
		{
			FlowUpdateTimeInSec = Ability->GetAbilityCompletionTime();
		}

		TargetComponent->SetTargetStrategy(this);
		PlayerController->OnPlayerSecondaryClickStarted.AddDynamic(this, &UFlowTargetStrategy::OnPlayerClickStarted);
		PlayerController->OnPlayerSecondaryClickStopped.AddDynamic(this, &UFlowTargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UFlowTargetStrategy::UpdateStrategy(float DeltaTime)
{
	if (!bFlowStart)
		return;
	
	if (!Ability->CanCastAbility())
	{
		CancelStrategy();
		return;
	}
	
	FVector PlayerDir;
	FocusComponent->GetPlayerLookAtNormalized(PlayerDir);
	FRotator PlayerRot = UKismetMathLibrary::MakeRotFromX(PlayerDir);

	FVector StartTrace = MuzzleComponent->GetComponentLocation();
	FVector EndTrace = MuzzleComponent->GetComponentLocation() + PlayerDir * AbilityDistance;
	
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
			Ability->ApplyAbilityEffect(HitResult.GetActor());
			CachedActors.Add(HitResult.GetActor());
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
				Ability->ApplyAbilityEffect(HitResults[i].GetActor());
				CachedActors.Add(HitResults[i].GetActor());
			}
		}
	}

	GetWorld()->DebugDrawTraceTag = NAME_None; 
	
	if (CurrentFlowCooldown > 0.0f)
	{
		CurrentFlowCooldown -= DeltaTime;
		
		if (CurrentFlowCooldown <= 0.001f)
			CurrentFlowCooldown = 0.0f;
		return;
	}
	
	if (CurrentFlowCooldown == 0.0f)
	{
		Ability->TrySpendMana();

		CachedActors.Empty();
		
		CurrentFlowCooldown = FlowUpdateTimeInSec;
	}
}

void UFlowTargetStrategy::CancelStrategy()
{
	UTargetStrategy::CancelStrategy();
	
	PlayerController->OnPlayerSecondaryClickStarted.RemoveDynamic(this, &UFlowTargetStrategy::OnPlayerClickStarted);
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UFlowTargetStrategy::OnPlayerClickStopped);

	bFlowStart = false;
	
	if (AbilityVFXComponent)
		AbilityVFXComponent->DestroyInstance();
	
	if (TargetComponent->GetTargetStrategy() == this)
	{
		TargetComponent->ClearTargetStrategy();
	}

	CachedActors.Empty();

	FocusComponent = nullptr;
	PlayerController = nullptr;
	MuzzleComponent = nullptr;

	bIsTargeting = false;
	Ability = nullptr;
	TargetComponent = nullptr;
}

void UFlowTargetStrategy::OnPlayerClickStarted()
{
	bFlowStart = true;
	
	FVector VFXLoc;
	FocusComponent->GetPlayerLookAtNormalizedLocation(VFXLoc);

	//Ensure that we don't have instances of ability vfx
	if (AbilityVFXComponent)
		AbilityVFXComponent->DestroyInstance();
	
	
	AbilityVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(Ability->GetAbilityDataAsset()->AbilityVFX, MuzzleComponent, FName(),
						MuzzleComponent->GetComponentLocation(), MuzzleComponent->GetComponentRotation(),
						FVector(1.f, 1.f, 1.f), EAttachLocation::Type::KeepWorldPosition,
						true, ENCPoolMethod::None, true, true);
		/*UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Ability->GetAbilityDataAsset()->AbilityVFX,
					VFXLoc,
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);*/
}

void UFlowTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	CancelStrategy();
}
