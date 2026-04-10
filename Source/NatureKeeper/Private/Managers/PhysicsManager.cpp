#include "Managers/PhysicsManager.h"

#include "Interfaces/Follow.h"
#include "Interfaces/Freezable.h"
#include "Interfaces/Movable.h"
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
				UE_LOG(LogTemp, Display, TEXT("Increment Follow Assign"));
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
	UE_LOG(LogTemp, Display, TEXT("Add New Follow Element"));
}

bool APhysicsManager::RemoveTargetFollowMap(const TScriptInterface<UFollow>& FollowActor, bool bForceDelete)
{
	for (int i = 0; i < TargetFollowMap.Num(); i++)
	{
		if (TargetFollowMap[i].FollowActor.GetObject() == FollowActor.GetObject())
		{
			TargetFollowMap[i].AssignCount -= 1;
			UE_LOG(LogTemp, Display, TEXT("Decrease Follow Assign"));
			if (bForceDelete || TargetFollowMap[i].AssignCount == 0)
			{
				TargetFollowMap.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Remove Follow Actor From Array"));
			}
			return true;
		}
	}

	return false;
}

void APhysicsManager::StartFreezeActor(const TScriptInterface<UFreezable>& InFreezeActor)
{
	if (!InFreezeActor.GetObject())
		return;

	for (int i = 0; i < FreezedActors.Num(); i++)
	{
		if (FreezedActors[i].FreezeActor.GetObject() == InFreezeActor.GetObject())
		{
			FreezedActors[i].AssignCount += 1;
			UE_LOG(LogTemp, Display, TEXT("Increment Freeze Assign"));
			return;
		}
	}
	
	FFreezeData NewFreezeElement;
	NewFreezeElement.FreezeActor = InFreezeActor;
	NewFreezeElement.AssignCount = 1;
	FreezedActors.Add(NewFreezeElement);
	IFreezable::Execute_StartFreeze(InFreezeActor.GetObject());
	UE_LOG(LogTemp, Display, TEXT("Add New Freeze Element"));
}

bool APhysicsManager::StopFreezeActor(const TScriptInterface<UFreezable>& InFreezeActor, bool bForceDelete)
{
	for (int i = 0; i < FreezedActors.Num(); i++)
	{
		if (FreezedActors[i].FreezeActor.GetObject() == InFreezeActor.GetObject())
		{
			FreezedActors[i].AssignCount -= 1;
			UE_LOG(LogTemp, Display, TEXT("Decrease Freeze Assign"));
			if (bForceDelete || FreezedActors[i].AssignCount == 0)
			{
				IFreezable::Execute_StopFreeze(InFreezeActor.GetObject());
				FreezedActors.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Remove Freeze Actor From Array"));
			}
			return true;
		}
	}

	return false;
}

void APhysicsManager::StartSlowActor(const TScriptInterface<UMovable>& InMovableActor, const float InSlowPercent,
	const float InSlowTime, const float InStunTime)
{
	if (!InMovableActor.GetObject())
		return;
	
	for (int i = 0; i < SlowedActors.Num(); i++)
	{
		if (SlowedActors[i].MovableActor.GetObject() == InMovableActor.GetObject())
		{
			SlowedActors[i].SlowPercent = FMath::Max(SlowedActors[i].SlowPercent, InSlowPercent);
			SlowedActors[i].SlowTime = FMath::Max(SlowedActors[i].SlowTime, InSlowTime);
			if (SlowedActors[i].SlowPercent >= 1.0f)
			{
				StartStunActor(InMovableActor, InStunTime);
				SlowedActors.RemoveAt(i);
			}
			else
			{
				IMovable::Execute_StartSlow(InMovableActor.GetObject(), SlowedActors[i].SlowPercent);
			}

			return;
		}
	}
	
	if (InSlowPercent >= 1.0f)
	{
		StartStunActor(InMovableActor, InStunTime);
	}
	else
	{
		FSlowData NewSlowData;
		NewSlowData.MovableActor = InMovableActor.GetObject();
		NewSlowData.SlowPercent = InSlowPercent;
		NewSlowData.SlowTime = InSlowTime;
		IMovable::Execute_StartSlow(InMovableActor.GetObject(), InSlowPercent);
		SlowedActors.Add(NewSlowData);
	}
}

bool APhysicsManager::StopSlowActor(const TScriptInterface<UMovable>& InMovableActor, float InSlowPercent,
	bool bForceStop)
{
	if (!InMovableActor.GetObject())
		return false;
	
	for (int i = 0; i < SlowedActors.Num(); i++)
	{
		if (SlowedActors[i].MovableActor.GetObject() == InMovableActor.GetObject())
		{
			SlowedActors[i].SlowPercent -= InSlowPercent;
			if (bForceStop || SlowedActors[i].SlowPercent <= 0)
			{
				SlowedActors.RemoveAt(i);
			}
			return true;
		}
	}
	
	return false;
}

void APhysicsManager::StartIceSlowActor(const TScriptInterface<UMovable>& InMovableActor, float InSlowPercent)
{
	if (!InMovableActor.GetObject())
		return;
	
	for (int i = 0; i < IceSlowedActors.Num(); i++)
	{
		if (IceSlowedActors[i].MovableActor.GetObject() == InMovableActor.GetObject())
		{
			IceSlowedActors[i].AssignCount++;
			IceSlowedActors[i].SlowPercent = FMath::Max(IceSlowedActors[i].SlowPercent, InSlowPercent);
			
			IMovable::Execute_StartSlow(InMovableActor.GetObject(), SlowedActors[i].SlowPercent);
			
			return;
		}
	}
	
	FIceSlowData NewSlowData;
	NewSlowData.MovableActor = InMovableActor.GetObject();
	NewSlowData.SlowPercent = InSlowPercent;
	NewSlowData.AssignCount = 1;
	IMovable::Execute_StartSlow(InMovableActor.GetObject(), InSlowPercent);
	IceSlowedActors.Add(NewSlowData);
}

bool APhysicsManager::StopIceSlowActor(const TScriptInterface<UMovable>& InMovableActor, float InSlowPercent,
	bool bForceStop)
{
	
}

void APhysicsManager::StartStunActor(const TScriptInterface<UMovable>& InMovableActor, float InStunTime)
{
}

bool APhysicsManager::StopStunActor(const TScriptInterface<UMovable>& InMovableActor, bool bForceStop)
{
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
