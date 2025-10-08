// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/CellMovementInterface.h"
#include "CellMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UCellMovementComponent : public UActorComponent, public ICellMovementInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCellMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cell Movement")
	ACharacter* CharacterOwner;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cell Movement")
	ACell* CurrentCellStandOn;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cell Movement")
	ACell* CurrentMovingToCell;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cell Movement")
	ACell* CurrentTargetCell;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cell Movement")
	int32 CurrentMovingToCellIndex;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cell Movement")
	TArray<ACell*> CurrentMovingPath;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cell Movement")
	float CurrentCellMovementSpeed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cell Movement")
	float MaxCellMovementSpeed;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void InitCellComponent(ACharacter* NewCharacterOwner);

	virtual ACell* GetCellStandOn_Implementation() override;
	virtual ACell* GetCellMovingTo_Implementation() override;
	virtual int32 GetCellMovingToIndex_Implementation() override;
	virtual ACell* GetTargetCell_Implementation() override;
	virtual TArray<ACell*> GetPath_Implementation() override;
	virtual float GetCellMovementCurrentSpeed_Implementation() override;
	virtual float GetCellMovementMaxSpeed_Implementation() override;
	virtual void CellIdle_Implementation() override;
	virtual bool TryStartActiveMoveByPath_Implementation(const TArray<ACell*>& TargetCells) override;
	virtual bool TryStopActiveMoveByPath_Implementation() override;
};
