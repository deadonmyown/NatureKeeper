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

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<UFollow> FollowActor;
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<UTarget> TargetActor;
	UPROPERTY(BlueprintReadWrite)
	int32 AssignCount;
};

USTRUCT(BlueprintType)
struct FFreezeData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<UFreezable> FreezeActor;
	UPROPERTY(BlueprintReadWrite)
	int AssignCount;
};

USTRUCT(BlueprintType)
struct FSlowData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<UMovable> MovableActor;
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
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<UMovable> MovableActor;
	UPROPERTY(BlueprintReadWrite)
	float SlowPercent = 0.0f; //[0..1]
	UPROPERTY(BlueprintReadWrite)
	int AssignCount = 0;
};

USTRUCT(BlueprintType)
struct FStunData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<UMovable> MovableActor;
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
	void AddTargetFollowMap(const TScriptInterface<UFollow>& FollowActor, const TScriptInterface<UTarget>& TargetActor);
	UFUNCTION(BlueprintCallable, Category="Physics Manager")
	bool RemoveTargetFollowMap(const TScriptInterface<UFollow>& FollowActor, bool bForceDelete = false);
	void StartFreezeActor(const TScriptInterface<UFreezable>& InFreezeActor);
	bool StopFreezeActor(const TScriptInterface<UFreezable>& InFreezeActor, bool bForceDelete = false);
	void StartSlowActor(const TScriptInterface<UMovable>& InMovableActor, const float InSlowPercent, const float InSlowTime, const float InStunTime);
	bool StopSlowActor(const TScriptInterface<UMovable>& InMovableActor, float InSlowPercent, bool bForceStop = false);
	void StartIceSlowActor(const TScriptInterface<UMovable>& InMovableActor, float InSlowPercent);
	bool StopIceSlowActor(const TScriptInterface<UMovable>& InMovableActor, float InSlowPercent, bool bForceStop = false);
	void StartStunActor(const TScriptInterface<UMovable>& InMovableActor, float InStunTime);
	bool StopStunActor(const TScriptInterface<UMovable>& InMovableActor, bool bForceStop = false);

	virtual void Tick(float DeltaTime) override;
};
