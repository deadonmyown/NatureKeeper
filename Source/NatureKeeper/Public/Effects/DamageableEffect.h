// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableBaseEffect.h"
#include "EffectBase.h"
#include "DamageableEffect.generated.h"

class UDamageableEffectDataAsset;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UDamageableEffect : public UDamageableBaseEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int DamageAmount = 0;

	virtual bool InitEffect(UEffectDataAsset* InEffectDataAsset) override;
	virtual bool ApplyEffect(TScriptInterface<UAffectable> InAffectedObject) override;
	
};
