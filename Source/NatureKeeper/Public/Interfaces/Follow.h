#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Follow.generated.h"

UINTERFACE(BlueprintType)
class UFollow : public UInterface
{
	GENERATED_BODY()
};

class NATUREKEEPER_API IFollow
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Follow Interface")
	AActor* GetFollowActor();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Follow Interface")
	FVector GetFollowLocation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Follow Interface")
	FRotator GetFollowRotation();
};
