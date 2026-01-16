#include "Collision/AbilityDamageCollision.h"

#include "Interfaces/Damageable.h"


AAbilityDamageCollision::AAbilityDamageCollision()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAbilityDamageCollision::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UDamageable>()) return;
	
	if (DamageCollisionData.DamageableTypes.IsEmpty()
		&& !DamageCollisionData.DamageableTypes.Contains(IDamageable::Execute_GetDamageableType(OtherActor))) return;
	
	IDamageable::Execute_TakeDamage(OtherActor, DamageCollisionData.DamageAmount, EEffectElement::EE_Physical, SweepResult.ImpactNormal);

	if (!OtherActor->Implements<UAffectable>()) return;

	if (!AbilityDamageCollisionData.Ability) return;

	AbilityDamageCollisionData.Ability->ApplyAbilityEffect(OtherActor);
}

void AAbilityDamageCollision::InitAbilityDamageCollisionData(const FAbilityDamageCollisionData& NewDamageCollisionData)
{
	AbilityDamageCollisionData = NewDamageCollisionData;
}
