// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "DamageableInteractiveActor.generated.h"

class UHealthComponent;

UCLASS()
class NATUREKEEPER_API ADamageableInteractiveActor : public AInteractiveActor, public IAffectable, public IDamageable
{
	GENERATED_BODY()

public:
	ADamageableInteractiveActor();

protected:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damageable")
	EDamageableType DamageableType = EDamageableType::DT_Object;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Affectable")
	TArray<UEffectBase*> Effects;

	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void OnDeath(int MinValue);
	
	virtual void Heal_Implementation(int HealAmount) override;
	virtual void TakeDamage_Implementation(int Damage) override;
	virtual EDamageableType GetDamageableType_Implementation() override {return DamageableType; }

	virtual bool RegisterEffect_Implementation(UEffectBase* EffectToAdd) override;
	virtual bool UnregisterEffect_Implementation(UEffectBase* EffectToRemove) override;
	virtual FVector GetEffectLocation_Implementation() override;
};
