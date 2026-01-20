#include "InteractionSystem/NaturalSpring.h"

#include "NatureKeeperCharacter.h"
#include "NatureKeeperGameMode.h"
#include "InteractionSystem/NaturalSpringPowerSource.h"
#include "Managers/LevelManager.h"
#include "ResourceSystem/EvilComponent.h"
#include "ResourceSystem/HealthComponent.h"


ANaturalSpring::ANaturalSpring()
{
	EvilComponent = CreateDefaultSubobject<UEvilComponent>("EvilComponent");
	
	PrimaryActorTick.bCanEverTick = false;

	bIsAbsorbComplete = false;
}

void ANaturalSpring::OnAbsorbComplete(int MinEvilValue)
{
	bIsAbsorbComplete = true;
	
	GetWorld()->GetTimerManager().ClearTimer(EvilAbsorbTimer);
	
	InteractingPlayerCache = nullptr;

	if (OnNaturalSpringEvilAbsorbComplete.IsBound())
		OnNaturalSpringEvilAbsorbComplete.Broadcast(this);
}

void ANaturalSpring::OnAbsorbEvil()
{
	if (bIsAbsorbComplete) return;
	
	if (!InteractingPlayerCache) return;

	if (!CheckPowerSourcesConditions()) return;

	if (InteractingPlayerCache->GetEvilComponent()->GetMaxResourceValue() == InteractingPlayerCache->GetEvilComponent()->GetResourceValue()) return;
	
	EvilComponent->DecreaseResourceValue(1);
	InteractingPlayerCache->GetEvilComponent()->IncreaseResourceValue(1);
	
	if (OnNaturalSpringEvilAbsorb.IsBound())
		OnNaturalSpringEvilAbsorb.Broadcast(this, 1);
}

void ANaturalSpring::BeginPlay()
{
	Super::BeginPlay();

	EvilComponent->OnResourceValueReachMin.AddDynamic(this, &ANaturalSpring::OnAbsorbComplete);

	if (UWorld* World = GetWorld())
	{
		ANatureKeeperGameMode* GameMode = World->GetAuthGameMode<ANatureKeeperGameMode>();
		if (ALevelManager* LevelManager = GameMode->GetLevelManager())
		{
			LevelManagerCache = LevelManager;
			LevelManagerCache->RegisterNaturalSpring(this);
		}
	}
}

bool ANaturalSpring::CheckPowerSourcesConditions() const
{
	if (NaturalSpringPowerSources.IsEmpty()) return true;

	for (int i = 0; i < NaturalSpringPowerSources.Num(); i++)
	{
		if (!NaturalSpringPowerSources[i]->bIsPowerSourceRevived)
			return false;
	}
	
	return true;
}

bool ANaturalSpring::StartInteract_Implementation(AActor* InteractionInvoker)
{
	if (bIsAbsorbComplete) return false;

	if (!CheckPowerSourcesConditions()) return false;
	
	if (ANatureKeeperCharacter* InteractionPlayer = Cast<ANatureKeeperCharacter>(InteractionInvoker))
	{
		if (LevelManagerCache)
			LevelManagerCache->ChangeLevelPhase(ELevelPhase::LP_Final);
		
		InteractingPlayerCache = InteractionPlayer;
		GetWorld()->GetTimerManager().SetTimer(EvilAbsorbTimer, this, &ANaturalSpring::OnAbsorbEvil, EvilAbsorbTimeInSec, true);

		return true;
	}

	return false;
}

bool ANaturalSpring::StopInteract_Implementation(AActor* InteractionInvoker)
{
	if (ANatureKeeperCharacter* InteractionPlayer = Cast<ANatureKeeperCharacter>(InteractionInvoker))
	{
		if (LevelManagerCache)
			LevelManagerCache->ChangeLevelPhase(ELevelPhase::LP_Default);
		
		GetWorld()->GetTimerManager().ClearTimer(EvilAbsorbTimer);
		InteractingPlayerCache = nullptr;
		return true;
	}
	
	return false;
}