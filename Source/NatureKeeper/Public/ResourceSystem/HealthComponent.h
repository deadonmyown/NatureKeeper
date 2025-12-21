#pragma once

#include "CoreMinimal.h"
#include "EntityResourceComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UHealthComponent : public UEntityResourceComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health Component")
	float DamageInvincibleTime = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Health Component")
	float CurrDamageInvincibleTime = 0.0f;

public:
	virtual void DecreaseResourceValue(int DeltaValue) override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
