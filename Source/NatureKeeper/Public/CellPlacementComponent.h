// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CellPlacementComponent.generated.h"


class ACell;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UCellPlacementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCellPlacementComponent();

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cell")
	ACell* MainCell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cell")
	TArray<ACell*> CellBlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cell")
	TArray<ACell*> CellNeighbours;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
};
