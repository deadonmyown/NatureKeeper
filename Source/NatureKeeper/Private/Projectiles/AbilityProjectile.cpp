#include "Projectiles/AbilityProjectile.h"

#include "NatureKeeperGameMode.h"
#include "NatureKeeperUtils.h"
#include "Collision/DamageCollisionBase.h"
#include "Components/SphereComponent.h"
#include "Effects/Ability.h"
#include "Interfaces/Affectable.h"
#include "Managers/DamageCollisionSpawner.h"


AAbilityProjectile::AAbilityProjectile()
{
}

void AAbilityProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AAbilityProjectile::InitAbilityProjectile(UAbility* ProjectileAbility)
{
	Ability = ProjectileAbility;
}

void AAbilityProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CollisionComponent->GetMoveIgnoreActors().Contains(OtherActor)) return;
	
	if (Ability)
	{
		if (CachedFirePressDuration == FirePressMaxDuration && AbilityDamageCollisionClass)
		{
			if (ANatureKeeperGameMode* GameMode = GetWorld()->GetAuthGameMode<ANatureKeeperGameMode>())
			{
				FTransform HitTransform;
				HitTransform.SetLocation(Hit.ImpactPoint);
				FDamageCollisionData DamageCollisionData = FDamageCollisionData();
				FAbilityDamageCollisionData AbilityDamageCollisionData = FAbilityDamageCollisionData();
				AbilityDamageCollisionData.Ability = Ability;
				GameMode->GetDamageCollisionSpawner()
				->SpawnAbilityDamageCollision(AbilityDamageCollisionClass, HitTransform, DamageCollisionData, AbilityDamageCollisionData);
			}
		}
		else
		{
			if (OtherActor->Implements<UAffectable>())
			{
				Ability->ApplyAbilityEffect(OtherActor);
			}
		}
	}
	Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}
