// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectDataAsset.h"
#include "TickableHealEffectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UTickableHealEffectDataAsset : public UEffectDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int InitialHealAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int TickHealAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int TicksCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float TickAmount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* TickEffectVFX;

	virtual float GetEffectCompletionTime() const override {return TicksCount * TickAmount;}
};
