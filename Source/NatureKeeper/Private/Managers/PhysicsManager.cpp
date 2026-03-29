#include "Managers/PhysicsManager.h"

#include "Interfaces/Follow.h"
#include "Interfaces/Target.h"
#include "Kismet/KismetMathLibrary.h"

APhysicsManager::APhysicsManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APhysicsManager::AddTargetFollowMap(const TScriptInterface<UFollow>& FollowActor, const TScriptInterface<UTarget>& TargetActor)
{
	if (!FollowActor.GetObject() || !TargetActor.GetObject()) return;

	for (int i = 0; i < TargetFollowMap.Num(); i++)
	{
		if (TargetFollowMap[i].FollowActor.GetObject() == FollowActor.GetObject())
		{
			if (TargetFollowMap[i].TargetActor.GetObject() == TargetActor.GetObject())
			{
				TargetFollowMap[i].AssignCount += 1;
				UE_LOG(LogTemp, Display, TEXT("Add Assign"));
				return;
			}
			else
			{
				return;
			}
		}
	}

	FTargetFollowMap NewMap;
	NewMap.FollowActor = FollowActor;
	NewMap.TargetActor = TargetActor;
	NewMap.AssignCount = 1;
	TargetFollowMap.Add(NewMap);
	UE_LOG(LogTemp, Display, TEXT("Add NewMap"));
}

bool APhysicsManager::RemoveTargetFollowMap(const TScriptInterface<UFollow>& FollowActor, bool bForceDelete)
{
	for (int i = 0; i < TargetFollowMap.Num(); i++)
	{
		if (TargetFollowMap[i].FollowActor.GetObject() == FollowActor.GetObject())
		{
			TargetFollowMap[i].AssignCount -= 1;
			UE_LOG(LogTemp, Display, TEXT("Remove assign"));
			if (bForceDelete || TargetFollowMap[i].AssignCount == 0)
			{
				TargetFollowMap.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Remove"));
			}
			return true;
		}
	}

	return false;
}

void APhysicsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetFollowMap.IsEmpty())
	{
		for (int i = TargetFollowMap.Num() - 1; i >= 0; i--)
		{
			if (!IsValid(TargetFollowMap[i].FollowActor.GetObject()) || !IsValid(TargetFollowMap[i].TargetActor.GetObject()))
			{
				TargetFollowMap.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Force remove"));
				continue;
			};

			AActor* FollowActorRef = IFollow::Execute_GetFollowActor(TargetFollowMap[i].FollowActor.GetObject());

			if (!IsValid(FollowActorRef))
			{
				TargetFollowMap.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Force remove"));
				continue;
			}

			//Right now just simple interpolation, later will include gravitation and physics in computation etc.
			FVector ActorLocation = FollowActorRef->GetActorLocation();
			FVector TargetLocation = ITarget::Execute_GetTargetLocation(TargetFollowMap[i].TargetActor.GetObject());
			FVector GoalLocation = UKismetMathLibrary::VInterpTo(ActorLocation, TargetLocation, DeltaTime, TargetFollowInterpSpeed);
			FollowActorRef->SetActorLocation(GoalLocation);
		}
	}
}