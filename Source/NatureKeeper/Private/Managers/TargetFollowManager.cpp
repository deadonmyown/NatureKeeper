// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TargetFollowManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ATargetFollowManager::ATargetFollowManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATargetFollowManager::AddTargetFollowMap(AActor* FollowActor, const TScriptInterface<UTarget>& FollowTarget)
{
	if (!FollowActor) return;
	
	if (TargetFollowMap.Contains(FollowActor))
	{
		TargetFollowMap[FollowActor] = FollowTarget;
	}
	else
	{
		TargetFollowMap.Add(FollowActor, FollowTarget);
	}
}

bool ATargetFollowManager::RemoveTargetFollowMap(AActor* Key)
{
	if (!TargetFollowMap.Contains(Key))
		return false;

	TargetFollowMap.Remove(Key);
	return true;
}

void ATargetFollowManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetFollowMap.IsEmpty())
	{
		for (auto [FollowedActor, Target] : TargetFollowMap)
		{
			UE_LOG(LogTemp, Display, TEXT("Hello"));
			if (!FollowedActor || !Target.GetObject()) continue;

			//Right now just simple interpolation, later will include gravitation and physics in computation etc.
			FVector ActorLocation = FollowedActor->GetActorLocation();
			FVector TargetLocation = ITarget::Execute_GetTargetLocation(Target.GetObject());
			FVector GoalLocation = UKismetMathLibrary::VInterpTo(ActorLocation, TargetLocation, DeltaTime, TargetFollowInterpSpeed);
			FollowedActor->SetActorLocation(GoalLocation);
			UE_LOG(LogTemp, Display, TEXT("New location for %s = %s"), *FollowedActor->GetName(), *GoalLocation.ToString());
		}
	}
}
