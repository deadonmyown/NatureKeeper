// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CellMovable.generated.h"

class ACell;
// This class does not need to be modified.
UINTERFACE()
class UCellMovable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API ICellMovable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	ACell* GetCurrentCell();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	void MoveByPath(TArray<ACell*> NewPath);
};
