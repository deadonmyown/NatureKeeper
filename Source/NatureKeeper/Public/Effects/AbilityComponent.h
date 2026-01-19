// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UEffectDataAsset;
class UPlayerAbility;
class UManaComponent;
class UTargetComponent;
class UTargetStrategy;
class UAffectable;

class UEffectFactory;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UPlayerAbility* PlayerAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<UEffectDataAsset*> AvailableEffectDataAssets;

	UPROPERTY(BlueprintReadWrite, Category = "Ability")
	UManaComponent* ManaComponent;
	
	virtual void BeginPlay() override;

public:
	UAbilityComponent();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetAbilityTargetStrategy(UTargetStrategy* NewTargetStrategy);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void ClearAbilityTargetStrategy();
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void ClearAbilityEffects();
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AddAbilityEffect(UEffectDataAsset* DataAssetToAdd);
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AddAbilityEffectByIndex(int32 EffectIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	UPlayerAbility* GetAbility() const { return PlayerAbility; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability")
	const TArray<UEffectDataAsset*>& GetAvailableEffects() const { return AvailableEffectDataAssets; }
};
