#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveActor.generated.h"

UINTERFACE()
class UInteractiveActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IInteractiveActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StartInteract(ACharacter* InteractionInvoker);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StopInteract(ACharacter* InteractionInvoker);
};
