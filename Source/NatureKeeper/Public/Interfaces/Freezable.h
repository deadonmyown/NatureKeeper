#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Freezable.generated.h"

UINTERFACE()
class UFreezable : public UInterface
{
	GENERATED_BODY()
};

class NATUREKEEPER_API IFreezable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Freeze Interface")
	void StartFreeze();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Freeze Interface")
	void StopFreeze();
};
