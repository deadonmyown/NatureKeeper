#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EffectInterface.generated.h"

UINTERFACE()
class UEffectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IEffectInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect")
	bool ApplyEffect(AActor* InAffectedActor);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect")
	bool CancelEffect();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effect")
	AActor* GetAffectedActor();
};