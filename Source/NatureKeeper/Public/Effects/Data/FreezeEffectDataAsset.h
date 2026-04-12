// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffectDataAsset.h"
#include "FreezeEffectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFreezeEffectDataAsset : public UTickableDamageableEffectDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* FreezeEffectVFX;
};
