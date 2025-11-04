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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float ProjectileLifeSpan = 5.0f;
	
	virtual void BeginPlay() override;
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	UNiagaraSystem* HitNiagaraSystem;
	
	// Sphere collision component.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
 
	// Projectile movement component.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION(BlueprintCallable, Category = Projectile)
	virtual void FireProjectileInDirection(const FVector& Direction);
	UFUNCTION(BlueprintCallable, Category = Projectile)
	virtual void AddActorsToIgnore(AActor* NewActorToIgnore);

	// Function that is called when the projectile hits something.
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
