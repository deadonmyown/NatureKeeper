#include "Managers/LevelManager.h"

#include "Kismet/GameplayStatics.h"


ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelManager::OnLooseLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}

void ALevelManager::OnWinLevel()
{
	//TODO: transition on next level
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
