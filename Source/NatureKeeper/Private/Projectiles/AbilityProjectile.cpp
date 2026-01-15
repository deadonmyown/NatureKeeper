#include "Projectiles/AbilityProjectile.h"

#include "Components/SphereComponent.h"
#include "Effects/Ability.h"
#include "Interfaces/Affectable.h"


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
		if (OtherActor->Implements<UAffectable>())
		{
			Ability->ApplyAbilityEffect(OtherActor);
		}
	}
	Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}
