#include "NatureKeeperUtils.h"

#include "FocusComponent.h"
#include "IsometricCell.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperGameMode.h"
#include "NavigationSystem.h"
#include "Effects/EffectBase.h"
#include "Effects/EffectFactory.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TargetFollowManager.h"

class ANatureKeeperGameMode;

UEffectBase* UNatureKeeperUtils::CreateEffect(UObject* Outer, TSubclassOf<UEffectBase> EffectClass,
	UEffectDataAsset* EffectDataAsset)
{
	if (!Outer || !EffectClass || !EffectDataAsset) return nullptr;
	
	UEffectBase* NewEffect = NewObject<UEffectBase>(Outer, EffectClass);

	if (!NewEffect->InitEffect(EffectDataAsset)) return nullptr;
	
	return NewEffect;
}

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

ANatureKeeperGameMode* UNatureKeeperUtils::GetNatureKeeperGameMode(const UObject* WorldContextObject)
{
	return WorldContextObject->GetWorld()->GetAuthGameMode<ANatureKeeperGameMode>();
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
		if (NavSys->GetRandomPointInNavigableRadius(Origin, Radius, RandomPoint))
		{
			return RandomPoint.Location;
		}
	}
    
	// If NavMesh is missing or no reachable point found
	return Origin; 
}

float UNatureKeeperUtils::GetEffectFactoriesCompletionTime(const TArray<UEffectFactory*>& InEffectFactories)
{
	float CompletionTime = 0.0f;
	for (int i = 0; i < InEffectFactories.Num(); i++)
	{
		CompletionTime += InEffectFactories[i]->GetEffectCompletionTime();
	}

	return CompletionTime;
}

float UNatureKeeperUtils::GetEffectsCompletionTime(const TArray<UEffectBase*>& InEffects)
{
	float CompletionTime = 0.0f;
	for (int i = 0; i < InEffects.Num(); i++)
	{
		CompletionTime += InEffects[i]->GetEffectCompletionTime();
	}

	return CompletionTime;
}

float UNatureKeeperUtils::GetEffectsRemainingTime(const TArray<UEffectBase*>& InEffects)
{
	float RemainingTime = 0.0f;
	for (int i = 0; i < InEffects.Num(); i++)
	{
		RemainingTime += InEffects[i]->GetEffectRemainingTime();
	}
	
	return RemainingTime;
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