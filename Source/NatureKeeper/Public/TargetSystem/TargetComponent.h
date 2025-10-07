// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


class UTargetStrategy;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Aura")
	UTargetStrategy* TargetStrategy;

public:
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
