// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "PlayerAbility.generated.h"

UCLASS()
class NATUREKEEPER_API UPlayerAbility : public UAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	UTargetStrategy* TargetStrategy = nullptr;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void Target(UTargetComponent* InTargetComponent);
};
