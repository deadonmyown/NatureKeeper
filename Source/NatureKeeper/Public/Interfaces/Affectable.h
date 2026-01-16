// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Affectable.generated.h"

UENUM(BlueprintType)
enum class EEffectElement : uint8
{
	EE_None UMETA(DisplayName = "None"),
	EE_Physical UMETA(DisplayName = "Physical"),
	EE_Earth UMETA(DisplayName = "Earth"),
	EE_Fire UMETA(DisplayName = "Fire"),
	EE_Water UMETA(DisplayName = "Water"),
	EE_Wind UMETA(DisplayName = "Wind"),
	EE_Steam UMETA(DisplayName = "Steam"),
	EE_Poison UMETA(DisplayName = "Poison"),
	EE_Evil UMETA(DisplayName = "Evil"),
};

class UEffectBase;
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UAffectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IAffectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	bool RegisterEffect(UEffectBase* EffectToAdd);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	bool UnregisterEffect(UEffectBase* EffectToRemove);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	USceneComponent* GetEffectLocation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	TArray<EEffectElement> GetWeaknessEffectElements();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	TArray<EEffectElement> GetResistEffectElements();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Effects")
	TArray<UEffectBase*> GetEffects();
};
