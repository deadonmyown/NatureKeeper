// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableBaseEffect.h"
#include "EffectBase.h"
#include "TickableDamageableEffect.generated.h"

class UNiagaraSystem;
class UTickableDamageableEffectDataAsset;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UTickableDamageableEffect : public UDamageableBaseEffect
{
	GENERATED_BODY()

protected:
	FTimerHandle DamageTimerHandle;
	UPROPERTY()
	int CurrTick = 0;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int InitialDamageAmount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int TickDamageAmount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int TicksCount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	float TickAmount = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* TickEffectVFX;

	virtual bool InitEffect(UEffectDataAsset* InEffectDataAsset) override;
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
	virtual bool CancelEffect() override;

	virtual float GetEffectCompletionTime() const override;
	virtual float GetEffectRemainingTime() const override;

	UFUNCTION()
	void OnTickDamage();
};
