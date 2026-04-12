// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableEffect.h"
#include "TickableDamageableEffect.h"
#include "WindEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UWindEffect : public UTickableDamageableEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	float ThrowForce = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	FVector AdditionalThrowVector = FVector::UpVector;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	FVector ThrowNormal;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	UPrimitiveComponent* ThrowPrimitiveComponent;
	
	virtual bool InitEffect(const FEffectData& InEffectData) override;
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
	virtual bool CancelEffect() override;
};
