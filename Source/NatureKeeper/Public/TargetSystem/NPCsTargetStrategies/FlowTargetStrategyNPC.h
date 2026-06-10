// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetSystem/TargetData.h"
#include "TargetSystem/TargetStrategy.h"
#include "FlowTargetStrategyNPC.generated.h"

class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFlowTargetStrategyNPC : public UTargetStrategy
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UNiagaraComponent* AbilityVFXComponent;

	UPROPERTY()
	TArray<FFlowUpdateData> CachedActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float OverrideFlowUpdateTimeInSec = -1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float DefaultFlowUpdateTimeInSec = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	bool bHitSingleTarget = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float CapsuleRadius = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float CapsuleHalfHeight = 100.0f;

	float FlowUpdateTimeInSec = 1.0f;
	float CurrentFlowCooldown = 0.0f;
	
public:
	virtual bool StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void UpdateStrategy(float DeltaTime) override;
	virtual void CancelStrategy() override;
};
