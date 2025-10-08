// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectDataAsset.h"
#include "DamageableEffectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UDamageableEffectDataAsset : public UEffectDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int DamageAmount = 0;
};
