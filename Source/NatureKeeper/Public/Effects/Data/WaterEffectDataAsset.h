// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffectDataAsset.h"
#include "WaterEffectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UWaterEffectDataAsset : public UTickableDamageableEffectDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int SteamInitialDamageAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* SteamEffectVFX;
};
