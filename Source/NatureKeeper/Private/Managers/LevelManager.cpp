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
	for (int i = 1; i < LevelNames.Num(); i++)
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
		if (LevelNames[i-1] == CurrentLevelName)
		{
			UGameplayStatics::OpenLevel(this, LevelNames[i]);
			return;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("YOU WON)"));
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

void ALevelManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (ANaturalSpring* Spring : NaturalSprings)
	{
		if (IsValid(Spring))
		{
			Spring->OnNaturalSpringEvilAbsorbComplete.RemoveAll(this);
		}
	}

	NaturalSprings.Empty();

	Super::EndPlay(EndPlayReason);
}
