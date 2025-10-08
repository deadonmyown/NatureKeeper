// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectFactory.h"
#include "DamageableEffectFactory.generated.h"

class UDamageableEffectDataAsset;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UDamageableEffectFactory : public UEffectFactory
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UDamageableEffectDataAsset* EffectDataAsset;

public:
	virtual UEffectBase* CreateEffect() override;
};
