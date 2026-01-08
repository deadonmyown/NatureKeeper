// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "FocusHoldTargetStrategy.generated.h"

class UFocusComponent;
class ANatureKeeperPlayerController;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFocusHoldTargetStrategy : public UTargetStrategy
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UFocusComponent* FocusComponent;
	UPROPERTY()
	ANatureKeeperPlayerController* PlayerController;
	UPROPERTY()
	AActor* CachedFocusActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	float OverrideFocusUpdateTimeInSec = -1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	bool bCancelAbility = false;

	bool bFocusStart = false;
	float FocusUpdateTimeInSec = 1.0f;
	float CurrentFocusCooldown = 0.0f;
	float AbilityDistance = 1.0f;
	
public:
	virtual bool StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void UpdateStrategy(float DeltaTime) override;
	virtual void CancelStrategy() override;

	UFUNCTION()
	void OnPlayerClickStarted();
	UFUNCTION()
	void OnPlayerClickStopped(float StopTriggerTime);
};
