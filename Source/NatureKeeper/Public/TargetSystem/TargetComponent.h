// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


class UEffectDataAsset;
class UManaComponent;
class UAbility;
class UTargetStrategy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetSet, UTargetStrategy*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetCancel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Target")
	FOnTargetSet OnTargetSet;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Target")
	FOnTargetCancel OnTargetCancel;

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	UAbility* Ability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	TArray<UEffectDataAsset*> AvailableEffectDataAssets;
	
	UPROPERTY(BlueprintReadOnly, Category = "Target")
	UTargetStrategy* TargetStrategy;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	TArray<UTargetStrategy*> TargetStrategies;
	
	virtual void BeginPlay() override;
public:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	UTargetStrategy* DefaultTargetStrategy;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Target")
	void StartTargetStrategy();
	UFUNCTION(BlueprintCallable, Category = "Target")
	void SetTargetStrategy(UTargetStrategy* NewTargetStrategy);
	UFUNCTION(BlueprintCallable, Category = "Target")
	void ClearTargetStrategy();
	/** Cancel and clear target strategy, can be invoked by other systems to stop active target strategy */
	UFUNCTION(BlueprintCallable, Category = "Target")
	void CancelTargetStrategy();
	UFUNCTION(BlueprintCallable, Category = "Target")
	UTargetStrategy* GetTargetStrategy() const {return TargetStrategy;}
	UFUNCTION(BlueprintPure, Category = "Target")
	const TArray<UTargetStrategy*>& GetTargetStrategies() const {return TargetStrategies;}

	UFUNCTION(BlueprintCallable, Category = "Target")
	void ClearAbilityEffects();
	UFUNCTION(BlueprintCallable, Category = "Target")
	void AddAbilityEffect(UEffectDataAsset* DataAssetToAdd);
	UFUNCTION(BlueprintCallable, Category = "Target")
	void AddAbilityEffectByIndex(int32 EffectIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Target")
	UAbility* GetAbility() const { return Ability; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Target")
	const TArray<UEffectDataAsset*>& GetAvailableEffects() const { return AvailableEffectDataAssets; }

	UFUNCTION(BlueprintPure, Category = "Target")
	bool IsTargeting() const;
};
