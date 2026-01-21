// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableInteractiveActor.h"
#include "NaturalSpringPowerSource.generated.h"

UCLASS()
class NATUREKEEPER_API ANaturalSpringPowerSource : public ADamageableInteractiveActor
{
	GENERATED_BODY()

public:
	ANaturalSpringPowerSource();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Natural Spring")
	bool bIsPowerSourceRevived;

	virtual void OnRevive(int MaxValue) override;
	virtual void OnDeath(int MinValue) override;
	
	virtual void TakeDamage_Implementation(int Damage, EEffectElement EffectElement = EEffectElement::EE_Physical, FVector DamageNormal = FVector::ZeroVector) override;
};
