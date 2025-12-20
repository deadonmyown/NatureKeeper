#include "NatureKeeperUtils.h"

#include "FocusComponent.h"
#include "IsometricCell.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperGameMode.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TargetFollowManager.h"

class ANatureKeeperGameMode;

void UNatureKeeperUtils::SetPlayerFocusComponentAsTarget(const TScriptInterface<UFollow>& FollowActor)
{
	if (!FollowActor.GetObject()) return;

	UWorld* World = FollowActor.GetObject()->GetWorld();
	if (!World) return;

	ANatureKeeperGameMode* GM = World->GetAuthGameMode<ANatureKeeperGameMode>();
	if (!GM) return;

	ATargetFollowManager* Manager = GM->GetTargetFollowManager();
	if (!Manager) return;

	ANatureKeeperCharacter* Player = GetNatureKeeperCharacter(FollowActor.GetObject());
	if (!Player) return;

	Manager->AddTargetFollowMap(FollowActor, Player->GetFocusComponent());
}

void UNatureKeeperUtils::RemoveElementFromTargetFollowManager(const TScriptInterface<UFollow>& FollowActor)
{
	if (!FollowActor.GetObject()) return;

	UWorld* World = FollowActor.GetObject()->GetWorld();
	if (!World) return;

	ANatureKeeperGameMode* GM = World->GetAuthGameMode<ANatureKeeperGameMode>();
	if (!GM) return;

	ATargetFollowManager* Manager = GM->GetTargetFollowManager();
	if (!Manager) return;

	Manager->RemoveTargetFollowMap(FollowActor);
}

ANatureKeeperCharacter* UNatureKeeperUtils::GetNatureKeeperCharacter(const UObject* WorldContextObject,
                                                                     int32 PlayerIndex)
{
	return Cast<ANatureKeeperCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, PlayerIndex));
}

FVector UNatureKeeperUtils::GetRandomNavigableLocationInRadius(UObject* WorldContextObject, const FVector& Origin,
	const float Radius)
{
	if (!IsValid(WorldContextObject))
	{
		return FVector::ZeroVector;
	}

	UWorld* World = WorldContextObject->GetWorld();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

	if (NavSys)
	{
		FNavLocation RandomPoint;
		if (NavSys->GetRandomReachablePointInRadius(Origin, Radius, RandomPoint))
		{
			return RandomPoint.Location;
		}
	}
    
	// If NavMesh is missing or no reachable point found
	return Origin; 
}

float UNatureKeeperUtils::CalculatePerlinNoise2D(int XVertexIndex, int YVertexIndex,
                                                 float InNoiseScale, float InNoiseSeed)
{
	return FMath::PerlinNoise2D(FVector2D(XVertexIndex * InNoiseScale + InNoiseSeed,
		YVertexIndex * InNoiseScale + InNoiseSeed));
}

float UNatureKeeperUtils::CalculatePerlinNoise3D(FVector Point, float InNoiseScale, float InNoiseSeed)
{
	return FMath::PerlinNoise3D(Point * InNoiseScale + InNoiseSeed);
}