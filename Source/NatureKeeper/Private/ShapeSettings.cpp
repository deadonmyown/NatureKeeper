#include "ShapeSettings.h"

float UShapeSettings::Evaluate(FNoiseSetting InNoiseSetting, FVector Point)
{
	return 1.0f;
}

float UShapeSettings::GetMin(FNoiseSetting InNoiseSetting)
{
	return -1.0f;
}

float UShapeSettings::GetMax(FNoiseSetting InNoiseSetting)
{
	return 1.0f;
}

float UShapeSettings::Evaluate_01(FNoiseSetting InNoiseSetting, FVector Point)
{
	return 1.0f;
}

float UShapeSettings::GetMin_01(FNoiseSetting InNoiseSetting)
{
	return 0.0f;
}

float UShapeSettings::GetMax_01(FNoiseSetting InNoiseSetting)
{
	return 1.0f;
}
