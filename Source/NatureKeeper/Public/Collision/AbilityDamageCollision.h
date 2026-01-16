#pragma once

#include "CoreMinimal.h"
#include "Collision/DamageCollisionBase.h"
#include "AbilityDamageCollision.generated.h"

UCLASS()
class NATUREKEEPER_API AAbilityDamageCollision : public ADamageCollisionBase
{
	GENERATED_BODY()

public:
	AAbilityDamageCollision();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DamageCollision)
	FAbilityDamageCollisionData AbilityDamageCollisionData;
	
	virtual void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	UFUNCTION(BlueprintCallable, Category = DamageCollision)
	void InitAbilityDamageCollisionData(const FAbilityDamageCollisionData& NewDamageCollisionData);
};
