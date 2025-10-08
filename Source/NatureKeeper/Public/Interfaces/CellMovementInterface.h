// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CellMovementInterface.generated.h"

class ACell;
// This class does not need to be modified.
UINTERFACE()
class UCellMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API ICellMovementInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	ACell* GetCellStandOn();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	ACell* GetCellMovingTo();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	int32 GetCellMovingToIndex();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	ACell* GetTargetCell();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	TArray<ACell*> GetPath();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	float GetCellMovementCurrentSpeed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	float GetCellMovementMaxSpeed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	void CellIdle();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	bool TryStartActiveMoveByPath(const TArray<ACell*>& TargetCells);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell Movable")
	bool TryStopActiveMoveByPath();
};
