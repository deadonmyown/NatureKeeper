// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffectFactory.h"
#include "WaterEffectFactory.generated.h"

class UWaterEffectDataAsset;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UWaterEffectFactory : public UTickableDamageableEffectFactory
{
	GENERATED_BODY()

public:
	virtual UEffectBase* CreateEffect() override;
};
