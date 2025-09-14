// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IsometricGrid.generated.h"

class AIsometricCell;

UCLASS()
class NATUREKEEPER_API AIsometricGrid : public AActor
{
	GENERATED_BODY()

public:
	AIsometricGrid();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	FIntVector2 GridSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	FVector2D CellSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Isometric")
	TArray<AIsometricCell*> Cells;

public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Isometric")
	void CreateGrid();
};
