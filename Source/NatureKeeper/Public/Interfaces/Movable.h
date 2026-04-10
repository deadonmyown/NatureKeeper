#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Movable.generated.h"

UINTERFACE()
class UMovable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IMovable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movable Interface")
	void StartSlow(float InSlowPercent);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movable Interface")
	void StopSlow();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movable Interface")
	void StartStun();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movable Interface")
	void StopStun();
};
