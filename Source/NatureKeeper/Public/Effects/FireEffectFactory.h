// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffectFactory.h"
#include "FireEffectFactory.generated.h"

class UFireEffectDataAsset;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFireEffectFactory : public UTickableDamageableEffectFactory
{
	GENERATED_BODY()

public:
	virtual UEffectBase* CreateEffect() override;
};
