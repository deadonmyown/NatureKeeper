// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "FlowTargetStrategy.generated.h"

class UNiagaraComponent;
class UFocusComponent;
class ANatureKeeperPlayerController;

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
	virtual bool StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void UpdateStrategy(float DeltaTime) override;
	virtual void CancelStrategy(bool bClearAbility = false) override;

	UFUNCTION()
	void OnPlayerClickStarted();
	UFUNCTION()
	void OnPlayerClickStopped(float StopTriggerTime);
};
