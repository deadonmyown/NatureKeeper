// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Visitor.generated.h"

class UVisitable;
// This class does not need to be modified.
UINTERFACE()
class UVisitor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IVisitor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visitable")
	bool OnStartVisit(TScriptInterface<UVisitable> Visitable);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visitable")
	bool OnEndVisit(TScriptInterface<UVisitable> Visitable);
};
