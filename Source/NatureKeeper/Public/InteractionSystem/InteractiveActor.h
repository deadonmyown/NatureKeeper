#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "InteractiveActor.generated.h"

class UCellPlacementComponent;

UCLASS()
class NATUREKEEPER_API AInteractiveActor : public AActor, public IInteractiveActorInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UCellPlacementComponent* CellPlacement;

public:
	AInteractiveActor();

	virtual bool StartInteract_Implementation(AActor* InteractionInvoker) override;
	virtual bool StopInteract_Implementation(AActor* InteractionInvoker) override;
};
