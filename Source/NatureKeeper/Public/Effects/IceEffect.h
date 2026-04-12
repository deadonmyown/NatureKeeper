// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffect.h"
#include "IceEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UIceEffect : public UTickableDamageableEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	float IceSlowPercent = 0.0f;
	
	virtual bool InitEffect(const FEffectData& InEffectData) override;
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
	virtual bool CancelEffect() override;
};
