// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Target.h"
#include "Subsystems/WorldSubsystem.h"
#include "TargetFollowManager.generated.h"

/**
 * 
 */
UCLASS()
class NATUREKEEPER_API ATargetFollowManager : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Target Follow Manager")
	TMap<AActor*, TScriptInterface<UTarget>> TargetFollowMap;

	FTimerHandle TargetFollowTimerHandle;
	
public:
	UFUNCTION(BlueprintCallable, Category="Target Follow Manager")
	void AddTargetFollowMap(AActor* FollowActor, TScriptInterface<UTarget> FollowTarget);
};
