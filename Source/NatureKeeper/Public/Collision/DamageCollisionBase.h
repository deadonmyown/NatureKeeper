#pragma once

#include "CoreMinimal.h"
#include "Effects/Ability.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Damageable.h"
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
	float CollisionLifeSpan = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollisionSphereRadius = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EDamageableType> DamageableTypes = {
		EDamageableType::DT_GoodPlayer,
	EDamageableType::DT_GoodNPC,
	EDamageableType::DT_EvilNPC,
	EDamageableType::DT_EvilPlayer,
	EDamageableType::DT_Object};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageAmount = 0;
	
};

USTRUCT(BlueprintType)
struct FEffectDamageCollisionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEffectBase> EffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEffectDataAsset* EffectDataAsset = nullptr;
};

USTRUCT(BlueprintType)
struct FAbilityDamageCollisionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbility* Ability = nullptr;
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
