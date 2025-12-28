#include "Collision/EffectDamageCollision.h"

#include "Interfaces/Damageable.h"


AEffectDamageCollision::AEffectDamageCollision()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEffectDamageCollision::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (DamageCollisionData.DamageAmount <= 0) return;
	
	if (!OtherActor->Implements<UDamageable>()) return;
	
	if (DamageCollisionData.DamageableTypes.IsEmpty()
		&& !DamageCollisionData.DamageableTypes.Contains(IDamageable::Execute_GetDamageableType(OtherActor))) return;
	
	IDamageable::Execute_TakeDamage(OtherActor, DamageCollisionData.DamageAmount);
}