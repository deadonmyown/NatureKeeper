// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealBaseEffect.h"
#include "TickableHealEffect.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UTickableHealEffect : public UHealBaseEffect
{
	GENERATED_BODY()

protected:
	FTimerHandle HealTimerHandle;
	UPROPERTY()
	int CurrTick = 0;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int InitialHealAmount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int TickHealAmount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	int TicksCount = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	float TickAmount = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* TickEffectVFX;

	virtual bool InitEffect(const FEffectData& InEffectData) override;
	virtual bool ApplyEffect(const TScriptInterface<UAffectable>& InAffectedObject) override;
	virtual bool CancelEffect() override;

	virtual float GetEffectCompletionTime() const override;
	virtual float GetEffectRemainingTime() const override;

	UFUNCTION()
	void OnTickHeal();
};
