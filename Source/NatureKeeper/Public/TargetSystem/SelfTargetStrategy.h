// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetStrategy.h"
#include "SelfTargetStrategy.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API USelfTargetStrategy : public UTargetStrategy
{
	GENERATED_BODY()
public:
	virtual void StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent) override;
};
