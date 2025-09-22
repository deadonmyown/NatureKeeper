#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractiveActor.h"
#include "Interfaces/Visitable.h"
#include "Cell.generated.h"

class UAuraComponent;

UENUM(BlueprintType)
enum class ECellType : uint8
{
	ICT_Default,
	ICT_Block
};

UCLASS()
class NATUREKEEPER_API ACell : public AActor, public IInteractiveActor, public IVisitable
{
	GENERATED_BODY()

public:
	ACell();

	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UAuraComponent* AuraComponent;

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

	UFUNCTION(BlueprintNativeEvent, Category = "Pathfinding")
	USceneComponent* GetNavigationRoot();

	virtual bool StartInteract_Implementation(ACharacter* InteractionInvoker) override;
	virtual bool StopInteract_Implementation(ACharacter* InteractionInvoker) override;

	virtual bool StartVisit_Implementation(TScriptInterface<UVisitor>) override;
	virtual bool EndVisit_Implementation(TScriptInterface<UVisitor>) override;
};
