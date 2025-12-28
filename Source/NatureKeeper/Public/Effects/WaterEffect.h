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
	int SteamInitialDamageAmount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* SteamEffectVFX;

	virtual bool InitEffect(UEffectDataAsset* InEffectDataAsset) override;
	virtual bool ApplyEffect(TScriptInterface<UAffectable> InAffectedObject) override;
};
