#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveActorInterface.generated.h"

UINTERFACE()
class UInteractiveActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IInteractiveActorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StartInteract(ACharacter* InteractionInvoker);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StopInteract(ACharacter* InteractionInvoker);
};
