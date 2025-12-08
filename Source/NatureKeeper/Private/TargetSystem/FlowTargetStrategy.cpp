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

void UFlowTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
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
		PlayerController->OnPlayerClickStarted.AddDynamic(this, &UFlowTargetStrategy::OnPlayerClickStarted);
		PlayerController->OnPlayerClickStopped.AddDynamic(this, &UFlowTargetStrategy::OnPlayerClickStopped);
	}
}

void UFlowTargetStrategy::UpdateStrategy(float DeltaTime)
{
	if (!Ability->CanCastAbility())
	{
		CancelStrategy();
		return;
	}
	
	FVector PlayerDir;
	FocusComponent->GetPlayerLookAtNormalized(PlayerDir);
	FRotator PlayerRot = UKismetMathLibrary::MakeRotFromX(PlayerDir);

	if (AbilityVFXComponent)
	{
		AbilityVFXComponent->SetWorldLocation(MuzzleComponent->GetComponentLocation());
		AbilityVFXComponent->SetWorldRotation(PlayerRot);
	}
	
	if (CurrentFlowCooldown > 0.0f)
	{
		CurrentFlowCooldown -= DeltaTime;
		
		if (CurrentFlowCooldown < 0.0f)
			CurrentFlowCooldown = 0.0f;
		return;
	}
	
	if (bFlowStart && CurrentFlowCooldown == 0.0f)
	{
		if (bHitSingleTarget)
		{
			FHitResult HitResult;

			FCollisionShape BoxShape = FCollisionShape::MakeBox(HitBoxCollisionExtent);

			FCollisionQueryParams Params;
			Params.AddIgnoredActor(TargetComponent->GetOwner());
			Params.bTraceComplex = false;
			Params.bDebugQuery = true;

			bool bHit = GetWorld()->SweepSingleByChannel(
				HitResult,
				MuzzleComponent->GetComponentLocation(),
				MuzzleComponent->GetComponentLocation() + PlayerDir * AbilityDistance,
				PlayerRot.Quaternion(),
				CollisionChannels::ECC_Damageable,
				BoxShape,
				Params
			);

			Ability->TrySpendMana();

			if (HitResult.GetActor() && HitResult.GetActor()->Implements<UAffectable>())
			{
				Ability->ApplyAbilityEffect(HitResult.GetActor());
			}
		}
		else
		{
			TArray<FHitResult> HitResults;

			FCollisionShape BoxShape = FCollisionShape::MakeBox(HitBoxCollisionExtent);

			FCollisionQueryParams Params;
			Params.AddIgnoredActor(TargetComponent->GetOwner());
			Params.bTraceComplex = false;
			Params.bDebugQuery = true;

			bool bHit = GetWorld()->SweepMultiByChannel(
				HitResults,
				MuzzleComponent->GetComponentLocation(),
				MuzzleComponent->GetComponentLocation() + PlayerDir * AbilityDistance,
				PlayerRot.Quaternion(),
				CollisionChannels::ECC_Damageable,
				BoxShape,
				Params
			);

			Ability->TrySpendMana();
		
			for (int i = 0; i < HitResults.Num(); i++)
			{
				if (HitResults[i].GetActor()->Implements<UAffectable>())
				{
					Ability->ApplyAbilityEffect(HitResults[i].GetActor());
				}
			}
		}
		
		CurrentFlowCooldown = FlowUpdateTimeInSec;
	}
}

void UFlowTargetStrategy::CancelStrategy()
{
	PlayerController->OnPlayerClickStarted.RemoveDynamic(this, &UFlowTargetStrategy::OnPlayerClickStarted);
	PlayerController->OnPlayerClickStopped.RemoveDynamic(this, &UFlowTargetStrategy::OnPlayerClickStopped);

	bFlowStart = false;
	
	if (AbilityVFXComponent)
		AbilityVFXComponent->DestroyInstance();
	
	if (TargetComponent->GetTargetStrategy() == this)
	{
		TargetComponent->ClearTargetStrategy();
	}

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
	
	AbilityVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Ability->GetAbilityDataAsset()->AbilityVFX,
					VFXLoc,
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);
}

void UFlowTargetStrategy::OnPlayerClickStopped()
{
	CancelStrategy();
}
