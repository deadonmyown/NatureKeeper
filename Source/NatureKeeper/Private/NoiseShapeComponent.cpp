#include "NoiseShapeComponent.h"

#include "ShapeSettings.h"

UNoiseShapeComponent::UNoiseShapeComponent()
{
	ClearGeneratedData();
}


void UNoiseShapeComponent::BeginPlay()
{
	Super::BeginPlay();

}

FVector UNoiseShapeComponent::CalculateUnit(FVector LocationToEvaluate)
{
	float NoiseAdd = 0.0f;
	float FirstSettingValue = 0.0f;
	if (ShapeSettings)
	{
		if (ShapeSettings->NoiseSettings.Num() > 0)
		{
			FirstSettingValue = ShapeSettings->Evaluate(ShapeSettings->NoiseSettings[0], LocationToEvaluate);
			if (ShapeSettings->NoiseSettings[0].bIsEnabled)
			{
				NoiseAdd = FirstSettingValue;
			}
		}

		for (int i = 1; i < ShapeSettings->NoiseSettings.Num(); i++)
		{
			if (ShapeSettings->NoiseSettings[i].bIsEnabled)
			{
				float Mask = ShapeSettings->NoiseSettings[i].bUseFirstSettingsAsMask ? FirstSettingValue : 1.0f;
				NoiseAdd += ShapeSettings->Evaluate(ShapeSettings->NoiseSettings[i], LocationToEvaluate) * Mask;
			}
		}
	}
	
	float VertexLength = NoiseMultiplier * NoiseAdd;
	FVector ResultVertex = LocationToEvaluate + VertexLength;
	
	return ResultVertex;
}

float UNoiseShapeComponent::GetMin()
{
	if (bMinGenerated)
		return MinLength;
	
	float NoiseAdd = 0.0f;
	float FirstSettingValue = 0.0f;
	if (ShapeSettings)
	{
		if (ShapeSettings->NoiseSettings.Num() > 0)
		{
			FirstSettingValue = ShapeSettings->GetMin(ShapeSettings->NoiseSettings[0]);
			if (ShapeSettings->NoiseSettings[0].bIsEnabled)
			{
				NoiseAdd = FirstSettingValue;
			}
		}

		for (int i = 1; i < ShapeSettings->NoiseSettings.Num(); i++)
		{
			if (ShapeSettings->NoiseSettings[i].bIsEnabled)
			{
				float Mask = ShapeSettings->NoiseSettings[i].bUseFirstSettingsAsMask ? FirstSettingValue : 1.0f;
				NoiseAdd += ShapeSettings->GetMin(ShapeSettings->NoiseSettings[i]) * Mask;
			}
		}
	}

	MinLength = NoiseMultiplier * NoiseAdd;
	bMinGenerated = true;
	return MinLength;
}

float UNoiseShapeComponent::GetMax()
{
	if (bMaxGenerated)
		return MaxLength;
	
	float NoiseAdd = 0.0f;
	float FirstSettingValue = 0.0f;
	if (ShapeSettings)
	{
		if (ShapeSettings->NoiseSettings.Num() > 0)
		{
			FirstSettingValue = ShapeSettings->GetMax(ShapeSettings->NoiseSettings[0]);
			if (ShapeSettings->NoiseSettings[0].bIsEnabled)
			{
				NoiseAdd = FirstSettingValue;
			}
		}

		for (int i = 1; i < ShapeSettings->NoiseSettings.Num(); i++)
		{
			if (ShapeSettings->NoiseSettings[i].bIsEnabled)
			{
				float Mask = ShapeSettings->NoiseSettings[i].bUseFirstSettingsAsMask ? FirstSettingValue : 1.0f;
				NoiseAdd += ShapeSettings->GetMax(ShapeSettings->NoiseSettings[i]) * Mask;
			}
		}
	}

	MaxLength = NoiseMultiplier * NoiseAdd;
	bMaxGenerated = true;
	return MaxLength;
}

void UNoiseShapeComponent::ClearGeneratedData()
{
	MinLength = 0.0f;
	MaxLength = 1.0f;
	bMinGenerated = false;
	bMaxGenerated = false;
}

