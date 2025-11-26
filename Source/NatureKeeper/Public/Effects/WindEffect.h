// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableEffect.h"
#include "TickableDamageableEffect.h"
#include "WindEffect.generated.h"

class UTargetFollowComponent;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UWindEffect : public UTickableDamageableEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Effects")
	UTargetFollowComponent* AttachedTargetFollow;

public:
	virtual bool ApplyEffect(TScriptInterface<UAffectable> InAffectedObject) override;
	virtual bool CancelEffect() override;
};
