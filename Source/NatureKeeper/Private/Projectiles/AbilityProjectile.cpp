#include "Projectiles/AbilityProjectile.h"

#include "NatureKeeperGameMode.h"
#include "NatureKeeperUtils.h"
#include "Collision/DamageCollisionBase.h"
#include "Collision/EffectDamageCollision.h"
#include "Components/SphereComponent.h"
#include "Effects/Ability.h"
#include "Effects/EffectBase.h"
#include "Interfaces/Affectable.h"
#include "Managers/DamageCollisionSpawner.h"


AAbilityProjectile::AAbilityProjectile()
{
}

void AAbilityProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AAbilityProjectile::InitAbilityProjectile(const TArray<UEffectDataAsset*> InAbilityEffects)
{
	ProjectileAbilityEffects = InAbilityEffects;
}

void AAbilityProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CollisionComponent->GetMoveIgnoreActors().Contains(OtherActor)) return;
	
	if (!ProjectileAbilityEffects.IsEmpty())
	{
		if (CachedFirePressDuration == FirePressMaxDuration && EffectDamageCollisionClass)
		{
			if (ANatureKeeperGameMode* GameMode = GetWorld()->GetAuthGameMode<ANatureKeeperGameMode>())
			{
				FTransform HitTransform;
				HitTransform.SetLocation(Hit.ImpactPoint);
				FDamageCollisionData DamageCollisionData = FDamageCollisionData();
				FEffectDamageCollisionData EffectDamageCollisionData = FEffectDamageCollisionData();
				EffectDamageCollisionData.EffectDataAsset = ProjectileAbilityEffects;
				GameMode->GetDamageCollisionSpawner()
				->SpawnEffectDamageCollision(EffectDamageCollisionClass, HitTransform, DamageCollisionData, EffectDamageCollisionData);
				DrawDebugSphere(GetWorld(), HitTransform.GetLocation(), DamageCollisionData.CollisionSphereRadius, 12,
					FColor::Red, false, DamageCollisionData.CollisionLifeSpan, 0, 1);
			}
		}
		else
		{
			if (OtherActor->Implements<UAffectable>())
			{
				UNatureKeeperUtils::TryCreateAndApplyEffects(this, ProjectileAbilityEffects, OtherActor);
			}
		}
	}
	Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}
