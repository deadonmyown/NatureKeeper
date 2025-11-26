// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NatureKeeperGameMode.generated.h"

class ATargetFollowManager;
class AWinManager;

UCLASS(minimalapi)
class ANatureKeeperGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY()
	AWinManager* WinManager;
	UPROPERTY(EditAnywhere, Category = "GameMode")
	TSubclassOf<AWinManager> WinManagerClass;
	UPROPERTY()
	ATargetFollowManager* TargetFollowManager;
	UPROPERTY(EditAnywhere, Category = "GameMode")
	TSubclassOf<ATargetFollowManager> TargetFollowManagerClass;

public:
	ANatureKeeperGameMode();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	AWinManager* GetWinManager() const {return WinManager;}
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	ATargetFollowManager* GetTargetFollowManager() const {return TargetFollowManager;}
};



