// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NatureKeeperGameMode.generated.h"

class AAuraManager;

UCLASS(minimalapi)
class ANatureKeeperGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameMode")
	TSubclassOf<AAuraManager> AuraManagerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameMode")
	AAuraManager* AuraManager;
public:
	ANatureKeeperGameMode();

	virtual void StartPlay() override;
	AAuraManager* GetAuraManager() const { return AuraManager; }
};



