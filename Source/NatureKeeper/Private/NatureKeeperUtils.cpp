#include "NatureKeeperUtils.h"

#include "IsometricCell.h"
#include "NatureKeeperCharacter.h"
#include "Kismet/GameplayStatics.h"

void UNatureKeeperUtils::SetPlayerFocusComponentAsTarget(UTargetFollowComponent* TargetFollowComponent)
{
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