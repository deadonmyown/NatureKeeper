// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Affectable.generated.h"

class UEffectBase;
// This class does not need to be modified.
UINTERFACE()
class UAffectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IAffectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	bool RegisterEffect(UEffectBase* EffectToAdd);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	bool UnregisterEffect(UEffectBase* EffectToRemove);
};
