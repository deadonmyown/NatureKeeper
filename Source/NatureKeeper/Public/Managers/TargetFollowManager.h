// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Target.h"
#include "Subsystems/WorldSubsystem.h"
#include "TargetFollowManager.generated.h"

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
class NATUREKEEPER_API ATargetFollowManager : public AActor
{
	GENERATED_BODY()

	ATargetFollowManager();

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

	virtual void Tick(float DeltaTime) override;
};
