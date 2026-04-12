#pragma once

#include "CoreMinimal.h"
#include "EffectData.generated.h"

class UEffectDataAsset;
/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FEffectHitData
{
	GENERATED_BODY()

	FEffectHitData():EffectImpactNormal(FVector::ZeroVector), EffectImpactLocation(FVector::ZeroVector), EffectHitComponent(nullptr){}
	FEffectHitData(const FVector& InEffectImpactNormal):
	EffectImpactNormal(InEffectImpactNormal), EffectImpactLocation(FVector::ZeroVector), EffectHitComponent(nullptr){}
	FEffectHitData(const FVector& InEffectImpactNormal, const FVector& InEffectImpactLocation):
	EffectImpactNormal(InEffectImpactNormal), EffectImpactLocation(InEffectImpactLocation), EffectHitComponent(nullptr){}
	FEffectHitData(const FVector& InEffectImpactNormal, UPrimitiveComponent* InEffectHitComponent):
	EffectImpactNormal(InEffectImpactNormal), EffectImpactLocation(FVector::ZeroVector), EffectHitComponent(InEffectHitComponent){}
	FEffectHitData(const FVector& InEffectImpactNormal, const FVector& InEffectImpactLocation, UPrimitiveComponent* InEffectHitComponent):
	EffectImpactNormal(InEffectImpactNormal), EffectImpactLocation(InEffectImpactLocation), EffectHitComponent(InEffectHitComponent){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FVector EffectImpactNormal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FVector EffectImpactLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UPrimitiveComponent* EffectHitComponent;
};

USTRUCT(Blueprintable, BlueprintType)
struct FEffectData
{
	GENERATED_BODY()

	FEffectData():EffectHitData(FEffectHitData()), EffectDataAsset(nullptr) {}
	FEffectData(const FEffectHitData& InEffectHitData):EffectHitData(InEffectHitData), EffectDataAsset(nullptr) {}
	FEffectData(const FEffectHitData& InEffectHitData, UEffectDataAsset* InEffectDataAsset):EffectHitData(InEffectHitData), EffectDataAsset(InEffectDataAsset) {}
	FEffectData(UEffectDataAsset* InEffectDataAsset):EffectHitData(FEffectHitData()), EffectDataAsset(InEffectDataAsset){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	FEffectHitData EffectHitData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UEffectDataAsset* EffectDataAsset;
};


