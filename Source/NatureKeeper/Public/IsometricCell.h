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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Isometric")
	EIsometricCellType CellType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Isometric")
	TArray<AIsometricCell*> Neighbours;

protected:
	virtual void BeginPlay() override;
};
