// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveCharacter.h"
#include "Interfaces/Affectable.h"
#include "Interfaces/Damageable.h"
#include "EnemyBaseCharacter.generated.h"

class USphereComponent;
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
	USphereComponent* AttackDetectorCollision;
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	EDamageableType EnemyType = EDamageableType::DT_EvilNPC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TArray<EDamageableType> DamageableActorTypes = {EDamageableType::DT_GoodPlayer, EDamageableType::DT_GoodNPC, EDamageableType::DT_Object};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TArray<UEffectBase*> Effects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	bool bIsAttacking = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	int AttackDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	float AttackDelay = 2.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy")
	float CurrAttackDelay;

	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
	bool StartAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enemy")
	void EndAttack();
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void Attack(const TScriptInterface<UDamageable>& DamageableActor, int InDamage);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enemy")
	bool CanAttack() const {return !bIsAttacking && CurrAttackDelay == 0.0f;}
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damageable")
	void Revive(int MaxValue);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damageable")
	void Death(int MinValue);
	UFUNCTION(BlueprintCallable, Category = "Damageable")
	virtual void OnRevive(int MaxValue);
	UFUNCTION(BlueprintCallable, Category = "Damageable")
	virtual void OnDeath(int MinValue);
	
	virtual void Heal_Implementation(int HealAmount) override;
	virtual void TakeDamage_Implementation(int Damage, EEffectElement EffectElement = EEffectElement::EE_Physical, FVector DamageNormal = FVector::ZeroVector) override;
	virtual EDamageableType GetDamageableType_Implementation() override {return EnemyType; }

	virtual bool RegisterEffect_Implementation(UEffectBase* EffectToAdd) override;
	virtual bool UnregisterEffect_Implementation(UEffectBase* EffectToRemove) override;
	virtual USceneComponent* GetEffectLocation_Implementation() override;
	virtual TArray<EEffectElement> GetWeaknessEffectElements_Implementation() override {return {};}
	virtual TArray<EEffectElement> GetResistEffectElements_Implementation() override {return {};}
	virtual TArray<UEffectBase*> GetEffects_Implementation() override {return Effects; }

};
