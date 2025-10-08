#pragma once

#include "CoreMinimal.h"
#include "IntVector2D.h"
#include "GameFramework/Actor.h"
#include "InteractionSystem/InteractiveActor.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Visitable.h"
#include "Cell.generated.h"


class UEvilComponent;

UENUM(BlueprintType)
enum class ECellType : uint8
{
	ICT_Default,
	ICT_Block
};

UCLASS()
class NATUREKEEPER_API ACell : public AInteractiveActor, public IVisitable, public IAffectable
{
	GENERATED_BODY()

public:
	ACell();

	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UEvilComponent* EvilComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Affectable")
	TArray<UEffectBase*> Effects;

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
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	virtual void ClearPathfinding();

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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Cell")
	void OnMinEvilEnergyValueReach(int MinValue);

	virtual bool StartInteract_Implementation(AActor* InteractionInvoker) override;
	virtual bool StopInteract_Implementation(AActor* InteractionInvoker) override;

	virtual bool StartVisit_Implementation(const TScriptInterface<UVisitor>& Visitor) override;
	virtual bool EndVisit_Implementation(const TScriptInterface<UVisitor>& Visitor) override;

	virtual bool RegisterEffect_Implementation(UEffectBase* EffectToAdd) override;
	virtual bool UnregisterEffect_Implementation(UEffectBase* EffectToRemove) override;
	virtual FVector GetEffectLocation_Implementation() override;
};
