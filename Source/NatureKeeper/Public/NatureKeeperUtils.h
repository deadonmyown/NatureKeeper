// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NatureKeeperUtils.generated.h"

class AIsometricCell;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UNatureKeeperUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintCallable, Category="Nature Keeper Util")
	static TArray<AIsometricCell*> FindPath(AIsometricCell* StartCell, AIsometricCell* TargetCell);
	UFUNCTION(BlueprintCallable, Category="Nature Keeper Util")
	static TArray<AIsometricCell*> FilterNeighbours(TArray<AIsometricCell*> Neighbours, TArray<AIsometricCell*> ProcessedCells);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Nature Keeper Util")
	static float CalculatePerlinNoise2D(int XVertexIndex, int YVertexIndex, float InNoiseScale, float InNoiseSeed);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Nature Keeper Util")
	static float CalculatePerlinNoise3D(FVector Point, float InNoiseScale, float InNoiseSeed);
};
