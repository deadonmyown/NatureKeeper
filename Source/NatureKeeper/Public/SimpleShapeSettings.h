
#pragma once

#include "CoreMinimal.h"
#include "ShapeSettings.h"
#include "SimpleShapeSettings.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API USimpleShapeSettings : public UShapeSettings
{
	GENERATED_BODY()

public:
	virtual float Evaluate(FNoiseSetting InNoiseSetting, FVector Point) override;
	virtual float GetMin(FNoiseSetting InNoiseSetting) override;
	virtual float GetMax(FNoiseSetting InNoiseSetting) override;

	virtual float Evaluate_01(FNoiseSetting InNoiseSetting, FVector Point) override;
	virtual float GetMin_01(FNoiseSetting InNoiseSetting) override;
	virtual float GetMax_01(FNoiseSetting InNoiseSetting) override;
	
};
