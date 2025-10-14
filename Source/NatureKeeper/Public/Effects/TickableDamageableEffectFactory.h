// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectFactory.h"
#include "TickableDamageableEffectFactory.generated.h"

class UTickableDamageableEffectDataAsset;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UTickableDamageableEffectFactory : public UEffectFactory
{
	GENERATED_BODY()

public:
	virtual UEffectBase* CreateEffect() override;
};
