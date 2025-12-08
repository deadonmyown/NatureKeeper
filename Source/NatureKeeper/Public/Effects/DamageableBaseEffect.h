// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectBase.h"
#include "DamageableBaseEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UDamageableBaseEffect : public UEffectBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	bool bIsWeakness = false;
	
public:
	virtual bool ApplyEffect(TScriptInterface<UAffectable> InAffectedObject) override;
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool TryDamage(int InDamageAmount, int InDamageMultiplier = 2);
};
