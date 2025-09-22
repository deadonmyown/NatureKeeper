// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Visitable.generated.h"

class UVisitor;
// This class does not need to be modified.
UINTERFACE()
class UVisitable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IVisitable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visitable")
	bool StartVisit(TScriptInterface<UVisitor>);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visitable")
	bool EndVisit(TScriptInterface<UVisitor>);
};
