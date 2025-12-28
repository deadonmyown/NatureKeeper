#pragma once

#include "CoreMinimal.h"
#include "DamageCollisionBase.h"
#include "EffectDamageCollision.generated.h"

UCLASS()
class NATUREKEEPER_API AEffectDamageCollision : public ADamageCollisionBase
{
	GENERATED_BODY()

public:
	AEffectDamageCollision();

protected:
	virtual void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
