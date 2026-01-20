#include "Managers/LevelManager.h"

#include "InteractionSystem/NaturalSpring.h"
#include "Kismet/GameplayStatics.h"


ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelManager::OnEvilAbsorbComplete(ANaturalSpring* CompletedNaturalSpring)
{
	for (int i = 0; i < NaturalSprings.Num(); i++)
	{
		if (!NaturalSprings[i]->IsAbsorbComplete())
			return;
	}

	OnWinLevel();
}

void ALevelManager::OnLooseLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}

void ALevelManager::OnWinLevel()
{
	UE_LOG(LogTemp, Display, TEXT("YOU WON)"));
	for (int i = 1; i < WorldList.Num(); i++)
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
		FString PreviousLevelName = UGameplayStatics::GetCurrentLevelName(WorldList[i-1], false);
		if (PreviousLevelName == CurrentLevelName)
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, WorldList[i]);
		}
	}
}

void ALevelManager::ChangeLevelPhase(const ELevelPhase& NewLevelPhase)
{
	if (CurrentLevelPhase == NewLevelPhase)
		return;
	
	CurrentLevelPhase = NewLevelPhase;

	if (OnLevelPhaseChanged.IsBound())
		OnLevelPhaseChanged.Broadcast(NewLevelPhase);
}

void ALevelManager::RegisterNaturalSpring(ANaturalSpring* NewNaturalSpring)
{
	if (NaturalSprings.Contains(NewNaturalSpring))
		return;

	NaturalSprings.Add(NewNaturalSpring);
	NewNaturalSpring->OnNaturalSpringEvilAbsorbComplete.AddDynamic(this, &ALevelManager::OnEvilAbsorbComplete);
}

void ALevelManager::UnregisterNaturalSpring(ANaturalSpring* NaturalSpringToRemove)
{
	if (!NaturalSprings.Contains(NaturalSpringToRemove))
		return;

	NaturalSprings.Remove(NaturalSpringToRemove);
}
