// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "AOETargetStrategy.generated.h"

class ANatureKeeperPlayerController;
class UFocusComponent;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UAOETargetStrategy : public UTargetStrategy
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UFocusComponent* FocusComponent;
	UPROPERTY()
	ANatureKeeperPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float AOERadius = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float AOEHalfHeight = 100.0f;
	
	float AbilityDistance = 0.0f;

public:
	virtual bool StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void CancelStrategy() override;

	UFUNCTION()
	void OnPlayerClickStopped(float StopTriggerTime);
};
