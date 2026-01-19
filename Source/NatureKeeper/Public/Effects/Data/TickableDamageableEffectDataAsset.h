// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectDataAsset.h"
#include "TickableDamageableEffectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UTickableDamageableEffectDataAsset : public UEffectDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int InitialDamageAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int TickDamageAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int TicksCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float TickAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* TickEffectVFX;

	virtual float GetEffectCompletionTime() const override {return TicksCount * TickAmount;}
};
