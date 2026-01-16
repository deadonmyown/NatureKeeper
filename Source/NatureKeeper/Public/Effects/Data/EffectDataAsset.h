// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EffectDataAsset.generated.h"

class UEffectBase;
enum class EEffectElement : uint8;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UEffectDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FName EffectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FText EffectDisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FText EffectDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	EEffectElement EffectElementType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<UEffectBase> BlendingEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UEffectDataAsset* BlendingEffectDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	EEffectElement BlendingEffectElementType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UTexture2D* EffectIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* EffectVFX;
};
