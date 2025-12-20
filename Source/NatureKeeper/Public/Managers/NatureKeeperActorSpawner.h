// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NatureKeeperActorSpawner.generated.h"

UCLASS()
class NATUREKEEPER_API ANatureKeeperActorSpawner : public AActor
{
	GENERATED_BODY()

public:
	ANatureKeeperActorSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnActorRadius = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnActorSpawnDelayInSec = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int MaxSpawnedActorsAmount = 5;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<AActor> SpawnActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<AActor*> SpawnedActors;

	UFUNCTION()
	void SpawnActor();
	UFUNCTION()
	void OnDestroySpawnedActor(AActor* DestroyedActor);
};
