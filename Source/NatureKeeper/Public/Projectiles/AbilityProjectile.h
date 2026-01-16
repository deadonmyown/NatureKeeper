// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "AbilityProjectile.generated.h"

class AAbilityDamageCollision;
class UAbility;

UCLASS()
class NATUREKEEPER_API AAbilityProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	AAbilityProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<AAbilityDamageCollision> AbilityDamageCollisionClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UAbility* Ability;

public:
	UFUNCTION(BlueprintCallable, Category = Projectile)
	virtual void InitAbilityProjectile(UAbility* ProjectileAbility);

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
};
