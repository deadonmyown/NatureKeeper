// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class NATUREKEEPER_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	float ProjectileLifeSpan = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	float ProjectileMagnitude = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	int ProjectileDamage = 0;
	
	virtual void BeginPlay() override;
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	UNiagaraSystem* HitNiagaraSystem;
	
	// Sphere collision component.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
 
	// Projectile movement component.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	float FirePressMinDuration = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	float FirePressMaxDuration = 3.0f;
	//Divider for FirePressDuration, result give us a speed multiplier
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
	float FirePressInfluence = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectile)
	float CachedFirePressDuration;

	UFUNCTION(BlueprintCallable, Category = Projectile)
	virtual void FireProjectileInDirection(const FVector& Direction, float FirePressDuration = 0.0f);
	UFUNCTION(BlueprintCallable, Category = Projectile)
	virtual void AddActorsToIgnore(AActor* NewActorToIgnore);

	// Function that is called when the projectile hits something.
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, Category = Projectile)
	void K2_OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
