// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EffectBase.generated.h"

class UAffectable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComplete, TScriptInterface<UAffectable>, AffectedObject);

UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UEffectBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable, Category="Effects")
	FOnComplete OnComplete;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Effects")
	TArray<TScriptInterface<UAffectable>> AffectedObjects;

public:
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool ApplyEffect(TArray<TScriptInterface<UAffectable>> InAffectedObjects);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool CancelEffectSingle(TScriptInterface<UAffectable> InAffectedObject);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool CancelEffect();
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual TArray<TScriptInterface<UAffectable>> GetAffectedObjects();
};
