// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "SelfTargetStrategy.generated.h"

class ANatureKeeperPlayerController;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API USelfTargetStrategy : public UTargetStrategy
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ANatureKeeperPlayerController* PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	FVector HitNormal;
	
public:
	virtual bool StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void CancelStrategy() override;

	UFUNCTION()
	void OnPlayerClickStarted();
	UFUNCTION()
	void OnPlayerClickStopped(float StopTriggerTime);
};
