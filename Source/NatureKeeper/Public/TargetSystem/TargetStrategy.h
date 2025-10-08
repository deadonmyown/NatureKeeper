// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TargetStrategy.generated.h"

class UAbility;
class UTargetComponent;
/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UTargetStrategy : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Target")
	UAbility* Ability;
	UPROPERTY(BlueprintReadOnly, Category = "Target")
	UTargetComponent* TargetComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Target")
	bool bIsTargeting = false;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void StartStrategy(UAbility* InAbility, UTargetComponent* InTargetComponent);
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void UpdateStrategy();
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void CancelStrategy();

	UFUNCTION(BlueprintCallable, Category = "Target")
	bool GetIsTargeting() const {return bIsTargeting;}
};
