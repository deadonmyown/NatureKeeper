// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NatureKeeperGameMode.generated.h"


UCLASS(minimalapi)
class ANatureKeeperGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANatureKeeperGameMode();

	virtual void StartPlay() override;
};



