#include "Managers/DamageCollisionSpawner.h"

#include "Collision/DamageCollisionBase.h"


ADamageCollisionSpawner::ADamageCollisionSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADamageCollisionSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

ADamageCollisionBase* ADamageCollisionSpawner::SpawnDamageCollision(
	const TSubclassOf<ADamageCollisionBase>& DamageCollisionClass, const FTransform& CollisionTransform, const FDamageCollisionData& DamageCollisionData)
{
	ADamageCollisionBase* DamageCollision = GetWorld()->SpawnActorDeferred<ADamageCollisionBase>(DamageCollisionClass, CollisionTransform, this);
	DamageCollision->InitDamageCollisionData(DamageCollisionData);

	return DamageCollision;
}

