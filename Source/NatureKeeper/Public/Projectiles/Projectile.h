// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class NATUREKEEPER_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:
	// Sphere collision component.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
 
	// Projectile movement component.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Projectile)
	virtual void FireProjectileInDirection(const FVector& Direction);

	// Function that is called when the projectile hits something.
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
