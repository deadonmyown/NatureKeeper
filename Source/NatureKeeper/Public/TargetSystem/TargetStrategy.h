// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TargetStrategy.generated.h"

class UPlayerAbility;
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
	UPlayerAbility* Ability;
	UPROPERTY(BlueprintReadOnly, Category = "Target")
	UTargetComponent* TargetComponent;
	UPROPERTY(BlueprintReadOnly, Category = "Target")
	bool bIsTargeting = false;
	UPROPERTY(BlueprintReadOnly, Category = "Target")
	bool bIsStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	int32 TargetStrategyManaCost = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float TargetStrategyAffectDistance = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UNiagaraSystem* TargetStrategyVFX;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UTexture2D* TargetStrategyIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FName TargetStrategyName;
	
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual bool StartStrategy(UPlayerAbility* InAbility, UTargetComponent* InTargetComponent);
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void UpdateStrategy(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Target")
	virtual void CancelStrategy(bool bClearAbility = false);

	UFUNCTION(BlueprintCallable, Category = "Target")
	bool GetIsTargeting() const {return bIsTargeting;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Target")
	bool GetIsStarted() const {return bIsStarted;}
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Target")
	UPlayerAbility* GetAbility() const {return Ability;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Target")
	int32 GetTargetStrategyManaCost() const {return TargetStrategyManaCost;}
};
