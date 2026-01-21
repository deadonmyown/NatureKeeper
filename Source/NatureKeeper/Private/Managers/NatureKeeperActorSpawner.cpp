#include "Managers/NatureKeeperActorSpawner.h"

#include "NatureKeeperUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/LevelManager.h"


ANatureKeeperActorSpawner::ANatureKeeperActorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ANatureKeeperActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ANatureKeeperActorSpawner::SpawnActor, SpawnActorSpawnDelayInSec, true);

	for (int i = 0; i < SpawnedActors.Num(); i++)
	{
		SpawnedActors[i]->OnDestroyed.AddDynamic(this, &ANatureKeeperActorSpawner::OnDestroySpawnedActor);
	}
}

void ANatureKeeperActorSpawner::SpawnActor()
{
	if (SpawnedActors.Num() >= MaxSpawnedActorsAmount)
		return;

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FVector SpawnLocation = UNatureKeeperUtils::GetRandomNavigableLocationInRadius(this, GetActorLocation(), SpawnActorRadius);
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);

	if (NewActor)
	{
		NewActor->OnDestroyed.AddDynamic(this, &ANatureKeeperActorSpawner::OnDestroySpawnedActor);

		SpawnedActors.Add(NewActor);
	}
}

void ANatureKeeperActorSpawner::OnDestroySpawnedActor(AActor* DestroyedActor)
{
	if (!IsValid(DestroyedActor) || !SpawnedActors.Contains(DestroyedActor))
		return;

	SpawnedActors.Remove(DestroyedActor);
}