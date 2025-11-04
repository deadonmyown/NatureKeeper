#include "Projectiles/Projectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


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

void AProjectile::FireProjectileInDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::AddActorsToIgnore(AActor* NewActorToIgnore)
{
	CollisionComponent->IgnoreActorWhenMoving(NewActorToIgnore, true);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                        UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}

	if (HitNiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitNiagaraSystem,
						Hit.ImpactPoint,
						FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
						true, true, ENCPoolMethod::None, true);
	}
	
	Destroy();
}
