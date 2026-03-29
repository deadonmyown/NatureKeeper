#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsManager.generated.h"

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

UCLASS()
class NATUREKEEPER_API APhysicsManager : public AActor
{
	GENERATED_BODY()

public:
	APhysicsManager();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Target Follow Manager")
	float TargetFollowInterpSpeed = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category="Target Follow Manager")
	TArray<FTargetFollowMap> TargetFollowMap;

	FTimerHandle TargetFollowTimerHandle;
	
public:
	UFUNCTION(BlueprintCallable, Category="Target Follow Manager")
	void AddTargetFollowMap(const TScriptInterface<UFollow>& FollowActor, const TScriptInterface<UTarget>& TargetActor);
	UFUNCTION(BlueprintCallable, Category="Target Follow Manager")
	bool RemoveTargetFollowMap(const TScriptInterface<UFollow>& FollowActor, bool bForceDelete = false);
	UFUNCTION(BlueprintCallable, Category="Target Follow Manager")
	bool TryToFreezeActor();

	virtual void Tick(float DeltaTime) override;
};
