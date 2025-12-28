#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageCollisionSpawner.generated.h"

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
	ADamageCollisionBase* SpawnDamageCollision(const TSubclassOf<ADamageCollisionBase>& DamageCollisionClass, const FTransform& CollisionTransform, const FDamageCollisionData& DamageCollisionData);
};
