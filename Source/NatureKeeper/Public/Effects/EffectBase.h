// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/EffectInterface.h"
#include "UObject/Object.h"
#include "EffectBase.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UEffectBase : public UObject, public IEffectInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Effects")
	AActor* AffectedActor;

public:
	virtual bool ApplyEffect_Implementation(AActor* InAffectedActor) override;
	virtual bool CancelEffect_Implementation() override;
	virtual AActor* GetAffectedActor_Implementation() override;
};
