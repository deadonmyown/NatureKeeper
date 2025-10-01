// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UAbility;
class UTargetComponent;
class UTargetStrategy;
class UAffectable;

class UEffectFactory;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NATUREKEEPER_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<UAbility*> Abilities;

public:
	// Sets default values for this component's properties
	UAbilityComponent();
};
