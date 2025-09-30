// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EffectFactory.generated.h"

class UEffectBase;
/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UEffectFactory : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	TArray<UEffectBase*> Effects;
public:
	UFUNCTION(BlueprintCallable, Category = "Effects")
	UEffectBase* CreateEffect();
	UFUNCTION(BlueprintCallable, Category = "Effects")
	bool AddEffect(UEffectBase* EffectToAdd);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	bool RemoveEffect(UEffectBase* EffectToRemove);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Effects")
	TArray<UEffectBase*>& GetEffects();
};
