// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableEffectDataAsset.h"
#include "EarthEffectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UEarthEffectDataAsset : public UDamageableEffectDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float SlowPercent = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float SlowTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float StunTime = 0.0f;
};
