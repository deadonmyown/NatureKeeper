// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/DamageableEffectFactory.h"
#include "EarthEffectFactory.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UEarthEffectFactory : public UDamageableEffectFactory
{
	GENERATED_BODY()

public:
	virtual UEffectBase* CreateEffect() override;
};
