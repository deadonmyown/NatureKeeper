#include "Collision/DamageCollisionBase.h"

#include "Components/SphereComponent.h"
#include "Interfaces/Damageable.h"

ADamageCollisionBase::ADamageCollisionBase()
{
	DamageCollision = CreateDefaultSubobject<USphereComponent>("DamageCollision");
	DamageCollision->SetSphereRadius(DamageCollisionData.CollisionSphereRadius);
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &ADamageCollisionBase::OnCollisionOverlap);

	InitialLifeSpan = DamageCollisionData.CollisionLifeSpan;
	
	PrimaryActorTick.bCanEverTick = false;
}

void ADamageCollisionBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Init Life Span = %f"), InitialLifeSpan);
}

void ADamageCollisionBase::InitDamageCollisionData(const FDamageCollisionData& NewDamageCollisionData)
{
	DamageCollisionData = NewDamageCollisionData;
}

void ADamageCollisionBase::SetDamageCollisionData(const FDamageCollisionData& NewDamageCollisionData)
{
	DamageCollisionData = NewDamageCollisionData;

	//Update Initial Data
	DamageCollision->SetSphereRadius(DamageCollisionData.CollisionSphereRadius);
	SetLifeSpan(DamageCollisionData.CollisionLifeSpan);
}

void ADamageCollisionBase::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (DamageCollisionData.DamageAmount <= 0) return;
	
	if (!OtherActor->Implements<UDamageable>()) return;
	
	if (DamageCollisionData.DamageableTypes.IsEmpty()
		&& !DamageCollisionData.DamageableTypes.Contains(IDamageable::Execute_GetDamageableType(OtherActor))) return;
	
	IDamageable::Execute_TakeDamage(OtherActor, DamageCollisionData.DamageAmount, EEffectElement::EE_Physical, SweepResult.ImpactNormal);
}
