// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealBaseEffect.h"
#include "HealEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UHealEffect : public UHealBaseEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int HealAmount = 0;

	virtual bool InitEffect(const FEffectData& InEffectData) override;
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
};
