#pragma once

#include "CoreMinimal.h"
#include "EntityResourceComponent.h"
#include "ManaComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UManaComponent : public UEntityResourceComponent
{
	GENERATED_BODY()

public:
	UManaComponent();

};
