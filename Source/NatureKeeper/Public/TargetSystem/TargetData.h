#pragma once

#include "CoreMinimal.h"
#include "TargetData.generated.h"

USTRUCT()
struct FFlowUpdateData
{
	GENERATED_BODY()

	FFlowUpdateData(){}

	FFlowUpdateData(AActor* InUpdateActor, float InRemainingTime):  UpdateActor(InUpdateActor), RemainingTime(InRemainingTime){}
	
	UPROPERTY()
	AActor* UpdateActor = nullptr;
	UPROPERTY()
	float RemainingTime = 0.0f;

	bool operator==(const FFlowUpdateData& Other) const {return Other.UpdateActor == UpdateActor;}
	bool operator==(const AActor* Other) const {return Other == UpdateActor;}
};
