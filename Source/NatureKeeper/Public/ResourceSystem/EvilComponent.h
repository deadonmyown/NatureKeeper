#pragma once

#include "CoreMinimal.h"
#include "EntityResourceComponent.h"
#include "EvilComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UEvilComponent : public UEntityResourceComponent
{
	GENERATED_BODY()

public:
	UEvilComponent();

};
