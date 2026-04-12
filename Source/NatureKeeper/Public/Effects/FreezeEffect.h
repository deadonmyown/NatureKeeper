// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableDamageableEffect.h"
#include "FreezeEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UFreezeEffect : public UTickableDamageableEffect
{
	GENERATED_BODY()

public:
	virtual bool InitEffect(const FEffectData& InEffectData) override;
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
	virtual bool CancelEffect() override;
};
