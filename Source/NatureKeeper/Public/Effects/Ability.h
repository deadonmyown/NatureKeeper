// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ability.generated.h"

class UAbilityDataAsset;
class UManaComponent;
class UAffectable;
class UTargetComponent;
class UEffectFactory;
class UTargetStrategy;

/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<UEffectFactory*> AbilityEffects;
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UTargetStrategy* TargetStrategy = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	UAbilityDataAsset* AbilityDataAsset;

	UPROPERTY(BlueprintReadWrite, Category = "Ability")
	UManaComponent* ManaComponent;
public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void InitAbility(UManaComponent* InManaComponent);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool CanCastAbility();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void Target(UTargetComponent* InTargetComponent);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void ApplyAbilityEffect(const TScriptInterface<UAffectable>& InAffectedObject);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	bool IsAbilityEffectsCompleted();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	float GetAbilityCompletionTime();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	bool TrySpendMana();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void CancelAbilityEffect();
	
	UFUNCTION(BlueprintPure, Category = "Ability")
	UAbilityDataAsset* GetAbilityDataAsset() const { return AbilityDataAsset; }
};
