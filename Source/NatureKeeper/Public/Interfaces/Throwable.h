// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Throwable.generated.h"

struct FThrowCommonParams;
// This class does not need to be modified.
UINTERFACE()
class UThrowable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IThrowable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Movable Interface")
	void AddThrowImpulse(UPrimitiveComponent* ThrowPrimitiveComponent, const FVector& InThrowDirection, const float InThrowStrength, const FThrowCommonParams& InParams);
};
