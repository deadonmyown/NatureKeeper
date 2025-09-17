#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class ACell;
class UNoiseShapeComponent;

UCLASS()
class NATUREKEEPER_API AGrid : public AActor
{
	GENERATED_BODY()

public:
	AGrid();
	
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UNoiseShapeComponent* NoiseShapeComponent;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	bool bCreateOnConstruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FIntVector2D GridSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FVector2D CellSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TSubclassOf<ACell> CellClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<ACell*> Cells;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	virtual void SetNeighbours();

public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Grid")
	virtual void CreateGrid();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Grid")
	virtual void ClearGrid();
};
