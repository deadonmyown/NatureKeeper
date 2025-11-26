#include "NatureKeeperUtils.h"

#include "FocusComponent.h"
#include "IsometricCell.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TargetFollowManager.h"

class ANatureKeeperGameMode;

void UNatureKeeperUtils::SetPlayerFocusComponentAsTarget(AActor* FollowActor)
{
	if (!FollowActor) return;

	UWorld* World = FollowActor->GetWorld();
	if (!World) return;

	ANatureKeeperGameMode* GM = World->GetAuthGameMode<ANatureKeeperGameMode>();
	if (!GM) return;

	ATargetFollowManager* Manager = GM->GetTargetFollowManager();
	if (!Manager) return;

	ANatureKeeperCharacter* Player = GetNatureKeeperCharacter(FollowActor);
	if (!Player) return;

	Manager->AddTargetFollowMap(FollowActor, Player->GetFocusComponent());
}

void UNatureKeeperUtils::RemoveElementFromTargetFollowManager(AActor* FollowActor)
{
	if (!FollowActor) return;

	UWorld* World = FollowActor->GetWorld();
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