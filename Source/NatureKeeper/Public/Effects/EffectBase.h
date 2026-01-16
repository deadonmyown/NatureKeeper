// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EffectBase.generated.h"


class UEffectDataAsset;
enum class EEffectElement : uint8;
class UNiagaraSystem;
class UEffectFactory;
class UAffectable;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStart, UEffectBase*, InEffect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComplete, UEffectBase*, InEffect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFail, UEffectBase*, InEffect);

UCLASS(BlueprintType, Blueprintable)
class NATUREKEEPER_API UEffectBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, BlueprintCallable, Category="Effects")
	FOnStart OnStart;
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, BlueprintCallable, Category="Effects")
	FOnComplete OnComplete;
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, BlueprintCallable, Category="Effects")
	FOnFail OnFail;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Effects")
	TScriptInterface<UAffectable> AffectedObject;
	
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* EffectVFX;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	EEffectElement EffectElementType;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UEffectBase> BlendingEffectClass;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	UEffectDataAsset* BlendingEffectDataAsset;
	UPROPERTY(BlueprintReadWrite, Category = "Effects")
	EEffectElement BlendingEffectElementType;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool InitEffect(UEffectDataAsset* InEffectDataAsset);
	
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool ApplyEffect(TScriptInterface<UAffectable> InAffectedObject);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool CancelEffect();
	UFUNCTION(BlueprintCallable, Category = "Effects")
	virtual bool TrySpawnVFX(UNiagaraSystem* InEffectVFX);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Effects")
	virtual float GetEffectCompletionTime() const {return 0.0f;}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Effects")
	virtual float GetEffectRemainingTime() const {return 0.0f;}
};
