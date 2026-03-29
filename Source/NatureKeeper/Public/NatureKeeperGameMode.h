// Copyright 1etmehear. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NatureKeeperGameMode.generated.h"

class APhysicsManager;
class ADamageCollisionSpawner;
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
	APhysicsManager* PhysicsManager;
	UPROPERTY(EditAnywhere, Category = "GameMode")
	TSubclassOf<APhysicsManager> PhysicsManagerClass;
	UPROPERTY()
	ADamageCollisionSpawner* DamageCollisionSpawner;
	UPROPERTY(EditAnywhere, Category = "GameMode")
	TSubclassOf<ADamageCollisionSpawner> DamageCollisionSpawnerClass;

public:
	ANatureKeeperGameMode();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	ALevelManager* GetLevelManager() const {return LevelManager;}
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	APhysicsManager* GetPhysicsManager() const {return PhysicsManager;}
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	ADamageCollisionSpawner* GetDamageCollisionSpawner() const {return DamageCollisionSpawner;}
};



