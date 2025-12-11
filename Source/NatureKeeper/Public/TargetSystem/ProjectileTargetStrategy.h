// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "ProjectileTargetStrategy.generated.h"

class AAbilityProjectile;
class ANatureKeeperPlayerController;
class UFocusComponent;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UProjectileTargetStrategy : public UTargetStrategy
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	USceneComponent* MuzzleComponent;
	UPROPERTY()
	UFocusComponent* FocusComponent;
	UPROPERTY()
	ANatureKeeperPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	TSubclassOf<AAbilityProjectile> ProjectileClass;
	
public:
	virtual void StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent) override;
	virtual void UpdateStrategy(float DeltaTime) override;
	virtual void CancelStrategy() override;

	UFUNCTION()
	void OnPlayerClickStopped(float StopTriggerTime);
};
