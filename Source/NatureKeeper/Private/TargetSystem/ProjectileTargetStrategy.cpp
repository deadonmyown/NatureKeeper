// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSystem/ProjectileTargetStrategy.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "Effects/Ability.h"
#include "Projectiles/AbilityProjectile.h"
#include "Projectiles/Projectile.h"
#include "TargetSystem/TargetComponent.h"

class ANatureKeeperCharacter;

bool UProjectileTargetStrategy::StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent)
{
	if (ANatureKeeperCharacter* Player = Cast<ANatureKeeperCharacter>(InTargetComponent->GetOwner()))
	{
		if (!UTargetStrategy::StartStrategy(InAbility, InTargetComponent))
			return false;
		
		FocusComponent = Player->GetFocusComponent();
		PlayerController = Player->GetNatureKeeperController();
		MuzzleComponent = FocusComponent->GetPlayerMuzzleComponent();

		bIsTargeting = true;
		Ability = InAbility;
		TargetComponent = InTargetComponent;

		TargetComponent->SetTargetStrategy(this);
		PlayerController->OnPlayerSecondaryClickStopped.AddDynamic(this, &UProjectileTargetStrategy::OnPlayerClickStopped);

		return true;
	}

	return false;
}

void UProjectileTargetStrategy::UpdateStrategy(float DeltaTime)
{
	
}

void UProjectileTargetStrategy::CancelStrategy()
{
	UTargetStrategy::CancelStrategy();
	
	PlayerController->OnPlayerSecondaryClickStopped.RemoveDynamic(this, &UProjectileTargetStrategy::OnPlayerClickStopped);
	
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

void UProjectileTargetStrategy::OnPlayerClickStopped(float StopTriggerTime)
{
	if (Ability && Ability->TrySpendMana())
	{
		FVector LookDirection;
		FocusComponent->GetPlayerLookAtNormalized(LookDirection);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = TargetComponent->GetOwner();
		SpawnParams.Instigator = TargetComponent->GetOwner()->GetInstigator();
		
		AAbilityProjectile* Projectile = GetWorld()->SpawnActor<AAbilityProjectile>(ProjectileClass, MuzzleComponent->GetComponentTransform(), SpawnParams);
		Projectile->AddActorsToIgnore(TargetComponent->GetOwner());
		Projectile->FireProjectileInDirection(LookDirection);
		Projectile->InitAbilityProjectile(Ability);
	}
	
	CancelStrategy();
}