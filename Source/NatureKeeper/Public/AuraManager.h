#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraManager.generated.h"

class UAuraComponent;

UCLASS()
class NATUREKEEPER_API AAuraManager : public AActor
{
	GENERATED_BODY()

public:
	AAuraManager();

protected:
	virtual void BeginPlay() override;

public:
	TArray<UAuraComponent*> Auras;
};
