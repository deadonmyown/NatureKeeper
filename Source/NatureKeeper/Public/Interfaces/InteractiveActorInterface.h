#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveActorInterface.generated.h"

UINTERFACE(BlueprintType)
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
	bool StartInteract(AActor* InteractionInvoker);
	virtual bool StartInteract_Implementation(AActor* InteractionInvoker);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StopInteract(AActor* InteractionInvoker);
	virtual bool StopInteract_Implementation(AActor* InteractionInvoker);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StartCursorFocus(AActor* InteractionInvoker);
	virtual bool StartCursorFocus_Implementation(AActor* InteractionInvoker);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StopCursorFocus(AActor* InteractionInvoker);
	virtual bool StopCursorFocus_Implementation(AActor* InteractionInvoker);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StartPlayerFocus(AActor* InteractionInvoker);
	virtual bool StartPlayerFocus_Implementation(AActor* InteractionInvoker);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InteractiveActor")
	bool StopPlayerFocus(AActor* InteractionInvoker);
	virtual bool StopPlayerFocus_Implementation(AActor* InteractionInvoker);
};
