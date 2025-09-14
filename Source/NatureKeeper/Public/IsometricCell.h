// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IsometricCell.generated.h"

UENUM(BlueprintType)
enum class EIsometricCellType : uint8
{
	ICT_Default,
	ICT_Block
};

UCLASS()
class NATUREKEEPER_API AIsometricCell : public AActor
{
	GENERATED_BODY()

public:
	AIsometricCell();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	EIsometricCellType CellType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	TArray<AIsometricCell*> Neighbours;
};
