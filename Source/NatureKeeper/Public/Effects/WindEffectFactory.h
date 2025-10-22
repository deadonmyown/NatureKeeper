// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableEffectFactory.h"
#include "WindEffectFactory.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UWindEffectFactory : public UDamageableEffectFactory
{
	GENERATED_BODY()

public:
	virtual UEffectBase* CreateEffect() override;
};
