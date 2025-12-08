// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveCharacter.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "EnemyBaseCharacter.generated.h"

class UHealthComponent;

UCLASS()
class NATUREKEEPER_API AEnemyBaseCharacter : public AInteractiveCharacter, public IAffectable, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();

protected:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damageable")
	EDamageableType DamageableType = EDamageableType::DT_EvilNPC;

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
	virtual USceneComponent* GetEffectLocation_Implementation() override;
	virtual TArray<EEffectElement> GetWeaknessEffectElements_Implementation() override {return {};}
	virtual TArray<EEffectElement> GetResistEffectElements_Implementation() override {return {};}
	virtual TArray<UEffectBase*> GetEffects_Implementation() override {return Effects; }
};
