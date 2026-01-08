#include "Managers/DamageCollisionSpawner.h"

#include "Collision/DamageCollisionBase.h"
#include "Collision/EffectDamageCollision.h"
#include "Kismet/GameplayStatics.h"


ADamageCollisionSpawner::ADamageCollisionSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADamageCollisionSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

ADamageCollisionBase* ADamageCollisionSpawner::SpawnDamageCollision(
	const TSubclassOf<ADamageCollisionBase>& InDamageCollisionClass, const FTransform& InCollisionTransform, const FDamageCollisionData& InDamageCollisionData)
{
	ADamageCollisionBase* DamageCollision = GetWorld()->SpawnActorDeferred<ADamageCollisionBase>(InDamageCollisionClass, InCollisionTransform, this);
	DamageCollision->InitDamageCollisionData(InDamageCollisionData);

	UGameplayStatics::FinishSpawningActor(DamageCollision, InCollisionTransform);

	return DamageCollision;
}

AEffectDamageCollision* ADamageCollisionSpawner::SpawnEffectDamageCollision(
	const TSubclassOf<AEffectDamageCollision>& InDamageCollisionClass, const FTransform& InCollisionTransform,
	const FDamageCollisionData& InDamageCollisionData, const FEffectDamageCollisionData& InEffectDamageCollisionData)
{
	AEffectDamageCollision* EffectDamageCollision = GetWorld()->SpawnActorDeferred<AEffectDamageCollision>(InDamageCollisionClass, InCollisionTransform, this);
	EffectDamageCollision->SetDamageCollisionData(InDamageCollisionData);
	EffectDamageCollision->InitEffectDamageCollisionData(InEffectDamageCollisionData);

	UGameplayStatics::FinishSpawningActor(EffectDamageCollision, InCollisionTransform);

	return EffectDamageCollision;
}

