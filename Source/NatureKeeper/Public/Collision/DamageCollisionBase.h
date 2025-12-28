// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageCollisionBase.generated.h"

class UEffectDataAsset;
class UEffectBase;
class USphereComponent;
enum class EDamageableType : uint8;

USTRUCT(BlueprintType)
struct FDamageCollisionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollisionLifeSpan = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollisionSphereRadius = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EDamageableType> DamageableTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageAmount = 10;
	
};

USTRUCT(BlueprintType)
struct FEffectDamageCollisionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	TSubclassOf<UEffectBase> EffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	UEffectDataAsset* EffectDataAsset = nullptr;
};

UCLASS()
class NATUREKEEPER_API ADamageCollisionBase : public AActor
{
	GENERATED_BODY()

public:
	ADamageCollisionBase();

protected:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true, NoEditInline))
	USphereComponent* DamageCollision;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = DamageCollision)
	FDamageCollisionData DamageCollisionData;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = DamageCollision)
	void InitDamageCollisionData(const FDamageCollisionData& NewDamageCollisionData);
	UFUNCTION(BlueprintCallable, Category = DamageCollision)
	virtual void SetDamageCollisionData(const FDamageCollisionData& NewDamageCollisionData);

protected:
	UFUNCTION()
	virtual void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
