// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API UAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	int AbilityManaCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FName AbilityName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FText AbilityDisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FText AbilityDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UTexture2D* AbilityIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UNiagaraSystem* AbilityVFX;
};
