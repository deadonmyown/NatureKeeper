// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Target.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API ITarget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	FVector GetTargetLocation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	FRotator GetTargetRotation();
};
