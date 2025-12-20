// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NatureKeeperGameMode.generated.h"

class ALevelManager;
class ATargetFollowManager;

UCLASS(minimalapi)
class ANatureKeeperGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY()
	ALevelManager* LevelManager;
	UPROPERTY(EditAnywhere, Category = "GameMode")
	TSubclassOf<ALevelManager> LevelManagerClass;
	UPROPERTY()
	ATargetFollowManager* TargetFollowManager;
	UPROPERTY(EditAnywhere, Category = "GameMode")
	TSubclassOf<ATargetFollowManager> TargetFollowManagerClass;

public:
	ANatureKeeperGameMode();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	ALevelManager* GetLevelManager() const {return LevelManager;}
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	ATargetFollowManager* GetTargetFollowManager() const {return TargetFollowManager;}
};



