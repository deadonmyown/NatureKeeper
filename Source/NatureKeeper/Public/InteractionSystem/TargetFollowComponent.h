// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetFollowComponent.generated.h"


class UTarget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UTargetFollowComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetFollowComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Target")
	TScriptInterface<UTarget> Target;
public:
	UFUNCTION(BlueprintCallable, Category="Target")
	void SetTarget(TScriptInterface<UTarget> NewTarget);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
