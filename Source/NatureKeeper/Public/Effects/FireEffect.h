// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffect.h"
#include "FireEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFireEffect : public UTickableDamageableEffect
{
	GENERATED_BODY()

public:
	virtual bool InitEffect(UEffectDataAsset* InEffectDataAsset) override;
};
