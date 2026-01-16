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

public:
	AInteractiveActor();
};
