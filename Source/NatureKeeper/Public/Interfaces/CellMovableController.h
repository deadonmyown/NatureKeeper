// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CellMovableController.generated.h"

class ACell;
// This class does not need to be modified.
UINTERFACE()
class UCellMovableController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API ICellMovableController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	ACell* GetCellMovingTo();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	int32 GetCellMovingToIndex();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	ACell* GetTargetCell();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	TArray<ACell*> GetPath();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	void StartActiveMoveByPath(TArray<ACell*> NewPath);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	void StopActiveMoveByPath();
};
