#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "InteractiveActor.generated.h"

UCLASS()
class NATUREKEEPER_API AInteractiveActor : public AActor, public IInteractiveActorInterface
{
	GENERATED_BODY()

public:
	AInteractiveActor();

	virtual bool StartInteract_Implementation(AActor* InteractionInvoker) override;
	virtual bool StopInteract_Implementation(AActor* InteractionInvoker) override;
};
