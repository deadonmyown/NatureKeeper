// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EffectFactory.generated.h"

class UEffectDataAsset;
class UEffectBase;
/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UEffectFactory : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Effects")
	TArray<UEffectBase*> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UEffectBase> EffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UEffectDataAsset* EffectDataAsset;
public:
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual UEffectBase* CreateEffect();
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void AddEffect(UEffectBase* EffectToAdd);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void RemoveEffect(UEffectBase* EffectToRemove);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Effects")
	TArray<UEffectBase*>& GetEffects();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Effects")
	UEffectDataAsset* GetEffectDataAsset() const {return EffectDataAsset;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Effects")
	float GetEffectCompletionTime();
};
