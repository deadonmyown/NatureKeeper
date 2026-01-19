// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


class UTargetStrategy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetSet, UTargetStrategy*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetClear);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Target")
	FOnTargetSet OnTargetSet;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Target")
	FOnTargetClear OnTargetClear;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Target")
	UTargetStrategy* TargetStrategy;
public:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	UTargetStrategy* DefaultTargetStrategy;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	UTargetStrategy* ProjectileTargetStrategy;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	UTargetStrategy* AOETargetStrategy;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	UTargetStrategy* FocusHoldTargetStrategy;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Target")
	UTargetStrategy* SelfTargetStrategy;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Target")
	void SetTargetStrategy(UTargetStrategy* NewTargetStrategy);
	UFUNCTION(BlueprintCallable, Category = "Target")
	void ClearTargetStrategy();
	/** Cancel and clear target strategy, can be invoked by other systems to stop active target strategy */
	UFUNCTION(BlueprintCallable, Category = "Target")
	void CancelTargetStrategy();
	UFUNCTION(BlueprintCallable, Category = "Target")
	UTargetStrategy* GetTargetStrategy() const {return TargetStrategy;}
};
