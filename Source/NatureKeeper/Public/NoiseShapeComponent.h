#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NoiseShapeComponent.generated.h"


class UShapeSettings;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UNoiseShapeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNoiseShapeComponent();

protected:
	virtual void BeginPlay() override;

public:
	/*Determine noise multiplier*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planets|Shape")
	float NoiseMultiplier = 1.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Shape")
	FVector CalculateUnit(FVector LocationToEvaluate);
	UFUNCTION(BlueprintCallable, Category = "Shape")
	float GetMin();
	UFUNCTION(BlueprintCallable, Category = "Shape")
	float GetMax();
	
	void ClearGeneratedData();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shape")
	float MinLength = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shape")
	float MaxLength = 1.0f;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Shape")
	UShapeSettings* ShapeSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shape")
	bool bMinGenerated = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Shape")
	bool bMaxGenerated = false;
};
