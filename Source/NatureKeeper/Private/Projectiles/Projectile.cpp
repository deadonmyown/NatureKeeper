#include "Projectiles/Projectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Damageable.h"


AProjectile::AProjectile()
{
	if(!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		RootComponent = CollisionComponent;

		// Event called when component hits something.
		CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}
 
	if(!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 1000.0f;
		ProjectileMovementComponent->MaxSpeed = 1000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->Bounciness = 0.0f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.1f;
	}

	InitialLifeSpan = ProjectileLifeSpan;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::FireProjectileInDirection(const FVector& Direction, float FirePressDuration)
{
	CachedFirePressDuration = FMath::Clamp(FirePressDuration, FirePressMinDuration, FirePressMaxDuration);
	const float SpeedMultiplier = CachedFirePressDuration / FirePressInfluence;
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed * SpeedMultiplier;
}

void AProjectile::AddActorsToIgnore(AActor* NewActorToIgnore)
{
	CollisionComponent->IgnoreActorWhenMoving(NewActorToIgnore, true);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                        UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CollisionComponent->GetMoveIgnoreActors().Contains(OtherActor)) return;
	
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * ProjectileMagnitude, Hit.ImpactPoint);
	}

	if (OtherActor->Implements<UDamageable>())
	{
		IDamageable::Execute_TakeDamage(OtherActor, ProjectileDamage, EEffectElement::EE_Physical, Hit.ImpactNormal);
	}

	if (HitNiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitNiagaraSystem,
						Hit.ImpactPoint,
						FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
						true, true, ENCPoolMethod::None, true);
	}

	K2_OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
	
	Destroy();
}
