// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShapeSettings.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FNoiseSetting
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	bool bIsEnabled;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	bool bUseFirstSettingsAsMask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float NoiseScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float NoiseSeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float NoiseAmplitude = 1.0f;

	/*Determine noise turbulence scale changing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float NoiseScaleMultiplier = 2.0f;

	/*Determine noise turbulence amplitude changing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float NoiseAmplitudeMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	int NoiseTurbulence = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float OffsetNoiseValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float MinNoiseValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float MaxNoiseValue = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float NegateNoiseStrength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise")
	float PositiveNoiseStrength = 1.0f;
	
};

UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UShapeSettings : public UObject
{
	GENERATED_BODY()

public:
	/* Return noise value in range from -1.0 to 1.0 */
	UFUNCTION(BlueprintCallable, Category = "Noise")
	virtual float Evaluate(FNoiseSetting InNoiseSetting, FVector Point);
	UFUNCTION(BlueprintCallable, Category = "Noise")
	virtual float GetMin(FNoiseSetting InNoiseSetting);
	UFUNCTION(BlueprintCallable, Category = "Noise")
	virtual float GetMax(FNoiseSetting InNoiseSetting);

	/* Return noise value in range (from 0.0 to 1.0) */
	UFUNCTION(BlueprintCallable, Category = "Noise")
	virtual float Evaluate_01(FNoiseSetting InNoiseSetting, FVector Point);
	UFUNCTION(BlueprintCallable, Category = "Noise")
	virtual float GetMin_01(FNoiseSetting InNoiseSetting);
	UFUNCTION(BlueprintCallable, Category = "Noise")
	virtual float GetMax_01(FNoiseSetting InNoiseSetting);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNoiseSetting> NoiseSettings;
};
