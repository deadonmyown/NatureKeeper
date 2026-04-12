// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffect.h"
#include "WaterEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UWaterEffect : public UTickableDamageableEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	float SlowPercent = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	float SlowTime = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	float StunTime = 0.0f;

	virtual bool InitEffect(const FEffectData& InEffectData) override;
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
};
