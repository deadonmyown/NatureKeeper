// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Affectable.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"


enum class EEffectElement : uint8;

UENUM(BlueprintType)
enum class EDamageableType : uint8
{
	DT_GoodPlayer,
	DT_GoodNPC,
	DT_EvilNPC,
	DT_EvilPlayer,
	DT_Object
};

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NATUREKEEPER_API IDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damageable")
	void Heal(int HealAmount);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damageable")
	void TakeDamage(int Damage, EEffectElement EffectElement = EEffectElement::EE_Physical, FVector DamageNormal = FVector::ZeroVector);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damageable")
	EDamageableType GetDamageableType();
};
