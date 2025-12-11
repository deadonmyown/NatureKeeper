// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "FlowTargetStrategy.generated.h"

class UNiagaraComponent;
class UFocusComponent;
class ANatureKeeperPlayerController;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFlowTargetStrategy : public UTargetStrategy
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	USceneComponent* MuzzleComponent;
	UPROPERTY()
	UFocusComponent* FocusComponent;
	UPROPERTY()
	ANatureKeeperPlayerController* PlayerController;
	UPROPERTY()
	UNiagaraComponent* AbilityVFXComponent;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float OverrideFlowUpdateTimeInSec = -1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	bool bHitSingleTarget = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	FVector HitBoxCollisionExtent = FVector(100.0f, 100.0f, 100.0f);

	bool bFlowStart = false;
	float FlowUpdateTimeInSec = 1.0f;
	float CurrentFlowCooldown = 0.0f;
	float AbilityDistance = 1.0f;
	
public:
	virtual void StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void UpdateStrategy(float DeltaTime) override;
	virtual void CancelStrategy() override;

	UFUNCTION()
	void OnPlayerClickStarted();
	UFUNCTION()
	void OnPlayerClickStopped(float StopTriggerTime);
};
