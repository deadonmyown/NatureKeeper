// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UManaComponent;
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
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TArray<UAbility*> Abilities;

	UPROPERTY(BlueprintReadWrite, Category = "Ability")
	UManaComponent* ManaComponent;
	
	virtual void BeginPlay() override;

public:
	UAbilityComponent();

	const TArray<UAbility*>& GetAbilities() const { return Abilities; }

	void InitComponent(UManaComponent* InManaComponent);
};
