#pragma once

#include "CoreMinimal.h"
#include "Collision/AbilityDamageCollision.h"
#include "GameFramework/Actor.h"
#include "DamageCollisionSpawner.generated.h"

struct FAbilityDamageCollisionData;
class AEffectDamageCollision;
struct FEffectDamageCollisionData;
struct FDamageCollisionData;
class ADamageCollisionBase;

UCLASS()
class NATUREKEEPER_API ADamageCollisionSpawner : public AActor
{
	GENERATED_BODY()

public:
	ADamageCollisionSpawner();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "DamageCollisionSpawner")
	ADamageCollisionBase* SpawnDamageCollision(const TSubclassOf<ADamageCollisionBase>& InDamageCollisionClass,
		const FTransform& InCollisionTransform, const FDamageCollisionData& InDamageCollisionData);
	UFUNCTION(BlueprintCallable, Category = "DamageCollisionSpawner")
	AEffectDamageCollision* SpawnEffectDamageCollision(const TSubclassOf<AEffectDamageCollision>& InDamageCollisionClass,
		const FTransform& InCollisionTransform, const FDamageCollisionData& InDamageCollisionData, const FEffectDamageCollisionData& InEffectDamageCollisionData);
	UFUNCTION(BlueprintCallable, Category = "DamageCollisionSpawner")
	AAbilityDamageCollision* SpawnAbilityDamageCollision(const TSubclassOf<AAbilityDamageCollision>& InAbilityDamageCollisionClass,
		const FTransform& InCollisionTransform, const FDamageCollisionData& InDamageCollisionData, const FAbilityDamageCollisionData& InAbilityDamageCollisionData);
};
