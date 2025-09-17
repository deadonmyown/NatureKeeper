#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractiveActor.h"
#include "Cell.generated.h"

UENUM(BlueprintType)
enum class ECellType : uint8
{
	ICT_Default,
	ICT_Block
};

UCLASS()
class NATUREKEEPER_API ACell : public AActor, public IInteractiveActor
{
	GENERATED_BODY()

public:
	ACell();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	ACell* PathConnection;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	int32 CostToStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	int32 CostToTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	FIntVector2D PathNodeCoord;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	ECellType CellType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cell")
	TArray<ACell*> Neighbours;

	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	virtual void SetCostToStart(int32 NewCost);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	virtual void SetCostToTarget(int32 NewCost);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	virtual void SetPathConnection(ACell* NewConnection);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	virtual void SetPathNodeCoord(FIntVector2D NewCoord);
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	virtual int32 GetDistanceToOtherCell(ACell* OtherPath);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	virtual int32 GetTotalCost() const {return CostToStart + CostToTarget;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	virtual int32 GetCostToStart() const {return CostToStart;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	virtual int32 GetCostToTarget() const {return CostToTarget;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	virtual ACell* GetPathConnection() const {return PathConnection;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pathfinding")
	virtual FIntVector2D GetPathNodeCoord() const {return PathNodeCoord;}

	virtual void StartInteract_Implementation(ACharacter* InteractionInvoker) override;
	virtual void StopInteract_Implementation(ACharacter* InteractionInvoker) override;
};
