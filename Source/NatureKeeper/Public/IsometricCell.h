// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractiveActor.h"
#include "IsometricCell.generated.h"

class UPathfindingComponent;

UENUM(BlueprintType)
enum class EIsometricCellType : uint8
{
	ICT_Default,
	ICT_Block
};

/*TODO: Think about architecture a bit more, should i pathfinding logic make more abstract (make separate component for example) and should
 *i make base class for isometric cell and grid */ 
UCLASS()
class NATUREKEEPER_API AIsometricCell : public AActor, public IInteractiveActor
{
	GENERATED_BODY()

public:
	AIsometricCell();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	AIsometricCell* PathConnection;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	int32 CostToStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	int32 CostToTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	FIntVector2D PathNodeCoord;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	EIsometricCellType CellType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Isometric")
	TArray<AIsometricCell*> Neighbours;

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void SetCostToStart(int32 NewCost);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void SetCostToTarget(int32 NewCost);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void SetPathConnection(AIsometricCell* NewConnection);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	void SetPathNodeCoord(FIntVector2D NewCoord);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	int32 GetDistanceToOtherCell(AIsometricCell* OtherPath);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	int32 GetTotalCost() const {return CostToStart + CostToTarget;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	int32 GetCostToStart() const {return CostToStart;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	int32 GetCostToTarget() const {return CostToTarget;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	AIsometricCell* GetPathConnection() const {return PathConnection;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	FIntVector2D GetPathNodeCoord() const {return PathNodeCoord;}

	virtual void StartInteract_Implementation(ACharacter* InteractionInvoker) override;
	virtual void StopInteract_Implementation(ACharacter* InteractionInvoker) override;
};
