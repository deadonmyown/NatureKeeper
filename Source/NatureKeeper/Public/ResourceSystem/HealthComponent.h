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
};
