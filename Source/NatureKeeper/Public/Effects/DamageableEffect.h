// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectBase.h"
#include "DamageableEffect.generated.h"

class UDamageableEffectDataAsset;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UDamageableEffect : public UEffectBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageableEffect")
	UDamageableEffectDataAsset* EffectDataAsset;

	virtual bool ApplyEffect(TScriptInterface<UAffectable> InAffectedObject) override;
	virtual bool CancelEffect() override;
	
};
