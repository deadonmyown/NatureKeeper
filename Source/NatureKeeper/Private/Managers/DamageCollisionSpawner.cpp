#include "Managers/DamageCollisionSpawner.h"

#include "Collision/AbilityDamageCollision.h"
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
	DamageCollision->SetDamageCollisionData(InDamageCollisionData);

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

AAbilityDamageCollision* ADamageCollisionSpawner::SpawnAbilityDamageCollision(
	const TSubclassOf<AAbilityDamageCollision>& InAbilityDamageCollisionClass, const FTransform& InCollisionTransform,
	const FDamageCollisionData& InDamageCollisionData, const FAbilityDamageCollisionData& InAbilityDamageCollisionData)
{
	AAbilityDamageCollision* AbilityDamageCollision = GetWorld()->SpawnActorDeferred<AAbilityDamageCollision>(InAbilityDamageCollisionClass,
		InCollisionTransform, this);
	AbilityDamageCollision->SetDamageCollisionData(InDamageCollisionData);
	AbilityDamageCollision->InitAbilityDamageCollisionData(InAbilityDamageCollisionData);

	UGameplayStatics::FinishSpawningActor(AbilityDamageCollision, InCollisionTransform);

	return AbilityDamageCollision;
}

