#include "Collision/EffectDamageCollision.h"

#include "NatureKeeperUtils.h"
#include "Effects/EffectBase.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"


AEffectDamageCollision::AEffectDamageCollision()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEffectDamageCollision::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UDamageable>()) return;
	
	if (DamageCollisionData.DamageableTypes.IsEmpty()
		&& !DamageCollisionData.DamageableTypes.Contains(IDamageable::Execute_GetDamageableType(OtherActor))) return;
	
	IDamageable::Execute_TakeDamage(OtherActor, DamageCollisionData.DamageAmount, EEffectElement::EE_Physical, SweepResult.ImpactNormal);

	if (!OtherActor->Implements<UAffectable>()) return;

	UEffectBase* NewEffect = UNatureKeeperUtils::CreateEffect(this, EffectDamageCollisionData.EffectClass, EffectDamageCollisionData.EffectDataAsset);

	if (!NewEffect) return;

	NewEffect->ApplyEffect(OtherActor);
}

void AEffectDamageCollision::InitEffectDamageCollisionData(const FEffectDamageCollisionData& NewDamageCollisionData)
{
	EffectDamageCollisionData = NewDamageCollisionData;
}
