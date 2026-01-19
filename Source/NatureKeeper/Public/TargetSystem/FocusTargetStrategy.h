// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "FocusTargetStrategy.generated.h"

class ANatureKeeperPlayerController;
class UFocusComponent;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFocusTargetStrategy : public UTargetStrategy
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UFocusComponent* FocusComponent;
	UPROPERTY()
	ANatureKeeperPlayerController* PlayerController;
	
public:
	virtual bool StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void UpdateStrategy(float DeltaTime) override;
	virtual void CancelStrategy(bool bClearAbility = false) override;

	UFUNCTION()
	void OnPlayerClickStopped(float StopTriggerTime);
};
