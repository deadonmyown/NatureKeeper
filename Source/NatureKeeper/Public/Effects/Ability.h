// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ability.generated.h"

class UAffectable;
class UTargetComponent;
class UEffectFactory;
class UTargetStrategy;

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	AT_Good,
	AT_Evil
};

/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<UEffectFactory*> GoodEffects;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<UEffectFactory*> EvilEffects;
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UTargetStrategy* TargetStrategy = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAbilityType AbilityType = EAbilityType::AT_Good;


public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void Target(UTargetComponent* InTargetComponent);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void ApplyAbilityEffect(const TScriptInterface<UAffectable>& InAffectedObject);
	/*UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void CancelAbilityEffect();*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void ChangeAbilityEffectsFactory(EAbilityType NewType);

	UFUNCTION(BlueprintPure, Category = "Ability")
	TArray<UEffectFactory*>& GetActualEffects() { return AbilityType == EAbilityType::AT_Good ? GoodEffects : EvilEffects; }
	UFUNCTION(BlueprintPure, Category = "Ability")
	EAbilityType GetActualAbilityType() const { return AbilityType; }
};
