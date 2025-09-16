// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "IsometricGrid.generated.h"

class UNoiseShapeComponent;
class AIsometricCell;

UCLASS()
class NATUREKEEPER_API AIsometricGrid : public AActor
{
	GENERATED_BODY()

public:
	AIsometricGrid();
	
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UNoiseShapeComponent* NoiseShapeComponent;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	bool bCreateOnConstruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	FIntVector2D GridSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	FVector2D CellSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	TSubclassOf<AIsometricCell> IsometricCellClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Isometric")
	TArray<AIsometricCell*> Cells;

	UFUNCTION(BlueprintCallable, Category = "Isometric")
	void SetNeighbours();

public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Isometric")
	void CreateGrid();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Isometric")
	void ClearGrid();

	
};
