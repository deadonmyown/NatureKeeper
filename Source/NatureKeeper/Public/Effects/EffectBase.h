// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EffectBase.generated.h"


enum class EEffectElement : uint8;
class UNiagaraSystem;
class UEffectFactory;
class UAffectable;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);
UCLASS(BlueprintType, Blueprintable)
class NATUREKEEPER_API UEffectBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, BlueprintCallable, Category="Effects")
	FOnComplete OnComplete;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Effects")
	UEffectFactory* EffectFactory = nullptr;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Effects")
	TScriptInterface<UAffectable> AffectedObject;
	
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* EffectVFX;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	EEffectElement EffectElementType;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool ApplyEffect(TScriptInterface<UAffectable> InAffectedObject);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool CancelEffect();
};
