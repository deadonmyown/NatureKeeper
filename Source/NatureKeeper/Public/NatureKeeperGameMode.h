// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NatureKeeperGameMode.generated.h"


class AWinManager;

UCLASS(minimalapi)
class ANatureKeeperGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY()
	AWinManager* WinManager;
	UPROPERTY(EditAnywhere, Category = "WinManager")
	TSubclassOf<AWinManager> WinManagerClass;

public:
	ANatureKeeperGameMode();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, category = "WinManager")
	AWinManager* GetWinManager() const {return WinManager;}
};



