// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectBase.h"
#include "HealBaseEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UHealBaseEffect : public UEffectBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	bool bIsResist = false;
	
public:
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool TryHeal(int InHealAmount, int InHealMultiplier = 2);
};
