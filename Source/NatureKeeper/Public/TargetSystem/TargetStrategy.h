// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TargetStrategy.generated.h"

class UTargetComponent;
class UAbilityComponent;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UTargetStrategy : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	UAbilityComponent* AbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	UTargetComponent* TargetComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	bool bIsTargeting = false;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void StartStrategy(UAbilityComponent* InAbility, UTargetComponent* InTargetComponent);
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void UpdateStrategy();
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void CancelStrategy();
};
