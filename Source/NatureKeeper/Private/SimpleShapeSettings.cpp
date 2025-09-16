// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShapeSettings.h"

#include "NatureKeeperUtils.h"

float USimpleShapeSettings::Evaluate(FNoiseSetting InNoiseSetting, FVector Point)
{
	float Result = 0.0;
	float NoiseScale = InNoiseSetting.NoiseScale;
	float NoiseAmplitude = InNoiseSetting.NoiseAmplitude;
	for(int32 i = 1; i <= InNoiseSetting.NoiseTurbulence; i++)
	{
		Result += UNatureKeeperUtils::CalculatePerlinNoise3D(Point,
			NoiseScale, InNoiseSetting.NoiseSeed) * NoiseAmplitude;
		NoiseScale *= InNoiseSetting.NoiseScaleMultiplier;
		NoiseAmplitude *= InNoiseSetting.NoiseAmplitudeMultiplier;
	}

	Result -= InNoiseSetting.OffsetNoiseValue;
	Result = FMath::Clamp(Result, InNoiseSetting.MinNoiseValue, InNoiseSetting.MaxNoiseValue);
	return Result < 0 ? Result * InNoiseSetting.NegateNoiseStrength : Result * InNoiseSetting.PositiveNoiseStrength;
}

float USimpleShapeSettings::GetMin(FNoiseSetting InNoiseSetting)
{
	float Result = 0.0;
	float NoiseAmplitude = InNoiseSetting.NoiseAmplitude;
	for(int32 i = 1; i <= InNoiseSetting.NoiseTurbulence; i++)
	{
		Result -= 0.5f * NoiseAmplitude;
		NoiseAmplitude *= InNoiseSetting.NoiseAmplitudeMultiplier;
	}

	Result -= InNoiseSetting.OffsetNoiseValue;
	Result = FMath::Clamp(Result, InNoiseSetting.MinNoiseValue, InNoiseSetting.MaxNoiseValue);
	return Result < 0 ? Result * InNoiseSetting.NegateNoiseStrength : Result * InNoiseSetting.PositiveNoiseStrength;
}

float USimpleShapeSettings::GetMax(FNoiseSetting InNoiseSetting)
{
	float Result = 0.0;
	float NoiseAmplitude = InNoiseSetting.NoiseAmplitude;
	for(int32 i = 1; i <= InNoiseSetting.NoiseTurbulence; i++)
	{
		Result += 0.5f * NoiseAmplitude;
		NoiseAmplitude *= InNoiseSetting.NoiseAmplitudeMultiplier;
	}

	Result -= InNoiseSetting.OffsetNoiseValue;
	Result = FMath::Clamp(Result, InNoiseSetting.MinNoiseValue, InNoiseSetting.MaxNoiseValue);
	return Result < 0 ? Result * InNoiseSetting.NegateNoiseStrength : Result * InNoiseSetting.PositiveNoiseStrength;
}

float USimpleShapeSettings::Evaluate_01(FNoiseSetting InNoiseSetting, FVector Point)
{
	float Result = 0.0;
	float NoiseScale = InNoiseSetting.NoiseScale;
	float NoiseAmplitude = InNoiseSetting.NoiseAmplitude;
	for(int32 i = 1; i <= InNoiseSetting.NoiseTurbulence; i++)
	{
		Result += (UNatureKeeperUtils::CalculatePerlinNoise3D(Point,
			NoiseScale, InNoiseSetting.NoiseSeed) + 1.0f) * 0.5f * NoiseAmplitude;
		NoiseScale *= InNoiseSetting.NoiseScaleMultiplier;
		NoiseAmplitude *= InNoiseSetting.NoiseAmplitudeMultiplier;
	}

	Result -= InNoiseSetting.OffsetNoiseValue;
	Result = FMath::Clamp(Result, InNoiseSetting.MinNoiseValue, InNoiseSetting.MaxNoiseValue);
	return Result < 0 ? Result * InNoiseSetting.NegateNoiseStrength : Result * InNoiseSetting.PositiveNoiseStrength;
}

float USimpleShapeSettings::GetMin_01(FNoiseSetting InNoiseSetting)
{
	float Result = -InNoiseSetting.OffsetNoiseValue;
	Result = FMath::Clamp(Result, InNoiseSetting.MinNoiseValue, InNoiseSetting.MaxNoiseValue);
	return Result < 0 ? Result * InNoiseSetting.NegateNoiseStrength : Result * InNoiseSetting.PositiveNoiseStrength;
}

float USimpleShapeSettings::GetMax_01(FNoiseSetting InNoiseSetting)
{
	float Result = 0.0;
	float NoiseAmplitude = InNoiseSetting.NoiseAmplitude;
	for(int32 i = 1; i <= InNoiseSetting.NoiseTurbulence; i++)
	{
		Result += 0.5f * NoiseAmplitude;
		NoiseAmplitude *= InNoiseSetting.NoiseAmplitudeMultiplier;
	}

	Result -= InNoiseSetting.OffsetNoiseValue;
	Result = FMath::Clamp(Result, InNoiseSetting.MinNoiseValue, InNoiseSetting.MaxNoiseValue);
	return Result < 0 ? Result * InNoiseSetting.NegateNoiseStrength : Result * InNoiseSetting.PositiveNoiseStrength;
}
