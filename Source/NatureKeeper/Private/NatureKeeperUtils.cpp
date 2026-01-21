#include "NatureKeeperUtils.h"

#include "FocusComponent.h"
#include "NatureKeeperCharacter.h"
#include "NatureKeeperGameMode.h"
#include "NavigationSystem.h"
#include "Effects/EffectBase.h"
#include "Effects/Data/EffectDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TargetFollowManager.h"

class ANatureKeeperGameMode;

UEffectBase* UNatureKeeperUtils::CreateEffect(UObject* Outer, UEffectDataAsset* EffectDataAsset)
{
	if (!Outer || !EffectDataAsset) return nullptr;
	
	UEffectBase* NewEffect = NewObject<UEffectBase>(Outer, EffectDataAsset->EffectClass);

	if (!NewEffect->InitEffect(EffectDataAsset)) return nullptr;
	
	return NewEffect;
}

void UNatureKeeperUtils::TryCreateAndApplyEffects(UObject* Outer, TArray<UEffectDataAsset*>& InEffectDataAssets,
	const TScriptInterface<UAffectable>& InAffectedObject)
{
	if (!Outer || InEffectDataAssets.IsEmpty() || !InAffectedObject.GetObject()) return;
	
	for (int i = 0; i < InEffectDataAssets.Num(); i++)
	{
		UEffectBase* NewEffect = CreateEffect(Outer, InEffectDataAssets[i]);

		if (!NewEffect) continue;
		
		NewEffect->ApplyEffect(InAffectedObject);
	}
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

	FNavLocation ProjectedPoint;
	if (!NavSys->ProjectPointToNavigation(Origin, ProjectedPoint, FVector(Radius, Radius, Radius)))
	{
		return Origin;
	}

	if (NavSys)
	{
		FNavLocation RandomPoint;
		if (NavSys->GetRandomPointInNavigableRadius(ProjectedPoint.Location, Radius, RandomPoint))
		{
			return RandomPoint.Location;
		}
	}
    
	// If NavMesh is missing or no reachable point found
	return ProjectedPoint.Location; 
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