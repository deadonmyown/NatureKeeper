// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ability.generated.h"

class UEffectDataAsset;
class UEffectBase;
class UManaComponent;
class UAffectable;
class UTargetComponent;
class UTargetStrategy;

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEffectDataAssetAdded, UAbility*, Ability, UEffectDataAsset*, NewDataAsset);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEffectDataAssetRemoved, UAbility*, Ability, UEffectDataAsset*, NewDataAsset);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectDataAssetClear, UAbility*, Ability);

UCLASS(DefaultToInstanced, Blueprintable, EditInlineNew)
class NATUREKEEPER_API UAbility : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnEffectDataAssetAdded OnEffectDataAssetAdded;
	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnEffectDataAssetRemoved OnEffectDataAssetRemoved;
	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnEffectDataAssetClear OnEffectDataAssetClear;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<UEffectDataAsset*> EffectDataAssets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	int32 MaxEffectsAmount = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Ability")
	UManaComponent* ManaComponent;
public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void InitManaComponent(UManaComponent* InManaComponent);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void ClearEffectDataAssets();
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AddEffectDataAssets(UEffectDataAsset* DataAssetToAdd);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RemoveEffectDataAssets(UEffectDataAsset* DataAssetToRemove);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetEffectDataAssets(const TArray<UEffectDataAsset*>& NewDataAssets);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool CanCastAbility();
	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual bool CanModifyAbility();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void ApplyAbilityEffect(const TScriptInterface<UAffectable>& InAffectedObject);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	float GetAbilityCompletionTime();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	bool TrySpendMana();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	virtual int32 GetManaCost();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	TArray<UEffectDataAsset*> GetEffectDataAssets() const {return EffectDataAssets;}
};
