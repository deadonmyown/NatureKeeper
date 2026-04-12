#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsManager.generated.h"

class UMovable;
class UFreezable;
class UTarget;
class UFollow;

USTRUCT(BlueprintType)
struct FTargetFollowMap
{
	GENERATED_BODY()

	//UFollow Interface
	UPROPERTY(BlueprintReadWrite)
	UObject* FollowActor;
	//UTarget Interface
	UPROPERTY(BlueprintReadWrite)
	UObject* TargetActor;
	UPROPERTY(BlueprintReadWrite)
	int32 AssignCount;
};

USTRUCT(BlueprintType)
struct FFreezeData
{
	GENERATED_BODY()

	//UFreezable Interface
	UPROPERTY(BlueprintReadWrite)
	UObject*  FreezeActor;
	UPROPERTY(BlueprintReadWrite)
	int AssignCount;
};

USTRUCT(BlueprintType)
struct FSlowData
{
	GENERATED_BODY()

	//UMovable Interface
	UPROPERTY(BlueprintReadWrite)
	UObject* MovableActor;
	UPROPERTY(BlueprintReadWrite)
	float SlowPercent = 0.0f; //[0..1] if == 1 => stun
	UPROPERTY(BlueprintReadWrite)
	float SlowTime = 0.0f;
};

//Compare to Slow data doesn't have time and can't stun actor
USTRUCT(BlueprintType)
struct FIceSlowData
{
	GENERATED_BODY()

	//UMovable Interface
	UPROPERTY(BlueprintReadWrite)
	UObject* MovableActor;
	UPROPERTY(BlueprintReadWrite)
	float SlowPercent = 0.0f; //[0..1]
	UPROPERTY(BlueprintReadWrite)
	int AssignCount = 0;
};

USTRUCT(BlueprintType)
struct FStunData
{
	GENERATED_BODY()
	//UMovable Interface
	UPROPERTY(BlueprintReadWrite)
	UObject* MovableActor;
	UPROPERTY(BlueprintReadWrite)
	float StunTime = 0.0f;
};

UCLASS()
class NATUREKEEPER_API APhysicsManager : public AActor
{
	GENERATED_BODY()

public:
	APhysicsManager();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Physics Manager")
	float TargetFollowInterpSpeed = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category="Physics Manager")
	TArray<FTargetFollowMap> TargetFollowMap;
	UPROPERTY(BlueprintReadOnly, Category="Physics Manager")
	TArray<FFreezeData> FreezedActors;
	UPROPERTY(BlueprintReadOnly, Category="Physics Manager")
	TArray<FSlowData> SlowedActors;
	UPROPERTY(BlueprintReadOnly, Category="Physics Manager")
	TArray<FIceSlowData> IceSlowedActors;
	UPROPERTY(BlueprintReadOnly, Category="Physics Manager")
	TArray<FStunData> StunnedActors;
	
public:
	UFUNCTION(BlueprintCallable, Category="Physics Manager")
	void AddTargetFollowMap(UObject* FollowActor, UObject* TargetActor);
	UFUNCTION(BlueprintCallable, Category="Physics Manager")
	bool RemoveTargetFollowMap(UObject* FollowActor, bool bForceDelete = false);
	void StartFreezeActor(UObject* InFreezeActor);
	bool StopFreezeActor(UObject* InFreezeActor, bool bForceDelete = false);
	void StartSlowActor(UObject* InMovableActor, const float InSlowPercent, const float InSlowTime, const float InStunTime);
	bool StopSlowActor(UObject* InMovableActor, float InSlowPercent, bool bForceStop = false);
	bool StopSlowActorByID(int32 InSlowActorID, bool bForceStop = false);
	void StartIceSlowActor(UObject* InMovableActor, float InSlowPercent);
	bool StopIceSlowActor(UObject* InMovableActor, float InSlowPercent, bool bForceStop = false);
	void StartStunActor(UObject* InMovableActor, float InStunTime);
	bool StopStunActor(UObject* InMovableActor, bool bForceStop = false);
	bool StopStunActorByID(int32 InStunActorID, bool bForceStop = false);
	void ThrowActor(UObject* InThrowableActor, UPrimitiveComponent* ThrowPrimitiveComponent, const FVector& InThrowNormal, const float InThrowForce);

	virtual void Tick(float DeltaTime) override;
};
