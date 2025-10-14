#include "Managers/WinManager.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/WinEntityComponent.h"


AWinManager::AWinManager()
{
}

void AWinManager::OnLooseLevel()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevelName));
}

void AWinManager::OnWinLevel()
{
	//TODO: transition on next level
	UE_LOG(LogTemp, Display, TEXT("YOU WON)"));
}

bool AWinManager::AddEntity(UWinEntityComponent* NewWinEntityComponent)
{
	if (WinEntityComponents.Contains(NewWinEntityComponent))
		return false;

	WinEntityComponents.Add(NewWinEntityComponent);
	NewWinEntityComponent->OnClearEntity.AddDynamic(this, &AWinManager::OnClearEntity);
	NewWinEntityComponent->OnReturnEntity.AddDynamic(this, &AWinManager::OnReturnEntity);
	return true;
}

bool AWinManager::RemoveEntity(UWinEntityComponent* ExistWinEntityComponent)
{
	if (!WinEntityComponents.Contains(ExistWinEntityComponent))
		return false;

	WinEntityComponents.Remove(ExistWinEntityComponent);
	ExistWinEntityComponent->OnClearEntity.RemoveDynamic(this, &AWinManager::OnClearEntity);
	ExistWinEntityComponent->OnReturnEntity.RemoveDynamic(this, &AWinManager::OnReturnEntity);
	return true;
}

void AWinManager::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (UWinEntityComponent* WinEntityComponent = Actor->FindComponentByClass<UWinEntityComponent>())
		{
			AddEntity(WinEntityComponent);
		}
	}
}

void AWinManager::OnClearEntity(UWinEntityComponent* ExistWinEntityComponent)
{
	RemoveEntity(ExistWinEntityComponent);

	if (WinEntityComponents.IsEmpty())
	{
		OnWinLevel();
	}
}

void AWinManager::OnReturnEntity(UWinEntityComponent* NewWinEntityComponent)
{
	AddEntity(NewWinEntityComponent);
}

