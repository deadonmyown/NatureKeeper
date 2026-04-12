#include "Managers/PhysicsManager.h"

#include "Interfaces/Follow.h"
#include "Interfaces/Freezable.h"
#include "Interfaces/Movable.h"
#include "Interfaces/Target.h"
#include "Interfaces/Throwable.h"
#include "Kismet/KismetMathLibrary.h"

APhysicsManager::APhysicsManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APhysicsManager::AddTargetFollowMap(UObject* FollowActor, UObject* TargetActor)
{
	if (!FollowActor || !TargetActor) return;

	for (int i = 0; i < TargetFollowMap.Num(); i++)
	{
		if (TargetFollowMap[i].FollowActor == FollowActor)
		{
			if (TargetFollowMap[i].TargetActor == TargetActor)
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

bool APhysicsManager::RemoveTargetFollowMap(UObject* FollowActor, bool bForceDelete)
{
	for (int i = 0; i < TargetFollowMap.Num(); i++)
	{
		if (TargetFollowMap[i].FollowActor == FollowActor)
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

void APhysicsManager::StartFreezeActor(UObject* InFreezeActor)
{
	if (!InFreezeActor)
		return;

	for (int i = 0; i < FreezedActors.Num(); i++)
	{
		if (FreezedActors[i].FreezeActor == InFreezeActor)
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
	IFreezable::Execute_StartFreeze(InFreezeActor);
	UE_LOG(LogTemp, Display, TEXT("Add New Freeze Element"));
}

bool APhysicsManager::StopFreezeActor(UObject* InFreezeActor, bool bForceDelete)
{
	for (int i = 0; i < FreezedActors.Num(); i++)
	{
		if (FreezedActors[i].FreezeActor == InFreezeActor)
		{
			FreezedActors[i].AssignCount -= 1;
			UE_LOG(LogTemp, Display, TEXT("Decrease Freeze Assign"));
			if (bForceDelete || FreezedActors[i].AssignCount == 0)
			{
				IFreezable::Execute_StopFreeze(InFreezeActor);
				FreezedActors.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Remove Freeze Actor From Array"));
			}
			return true;
		}
	}

	return false;
}

void APhysicsManager::StartSlowActor(UObject* InMovableActor, const float InSlowPercent,
	const float InSlowTime, const float InStunTime)
{
	if (!InMovableActor)
		return;
	
	for (int i = 0; i < SlowedActors.Num(); i++)
	{
		if (SlowedActors[i].MovableActor == InMovableActor)
		{
			SlowedActors[i].SlowPercent = FMath::Max(SlowedActors[i].SlowPercent, InSlowPercent);
			SlowedActors[i].SlowTime = FMath::Max(SlowedActors[i].SlowTime, InSlowTime);
			if (SlowedActors[i].SlowPercent >= 1.0f)
			{
				StopSlowActorByID(i, true);
				StartStunActor(InMovableActor, InStunTime);
			}
			else
			{
				IMovable::Execute_StartSlow(InMovableActor, SlowedActors[i].SlowPercent);
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
		NewSlowData.MovableActor = InMovableActor;
		NewSlowData.SlowPercent = InSlowPercent;
		NewSlowData.SlowTime = InSlowTime;
		IMovable::Execute_StartSlow(InMovableActor, InSlowPercent);
		SlowedActors.Add(NewSlowData);
	}
}

bool APhysicsManager::StopSlowActor(UObject* InMovableActor, float InSlowPercent,
	bool bForceStop)
{
	if (!InMovableActor)
		return false;
	
	for (int i = 0; i < SlowedActors.Num(); i++)
	{
		if (SlowedActors[i].MovableActor == InMovableActor)
		{
			SlowedActors[i].SlowPercent -= InSlowPercent;
			if (bForceStop || SlowedActors[i].SlowPercent <= 0)
			{
				bool bHasOtherSlowEffect = false;
				for (int j = 0; j < IceSlowedActors.Num(); j++)
				{
					if (IceSlowedActors[j].MovableActor == InMovableActor)
					{
						bHasOtherSlowEffect = true;
						break;
					}
				}
		
				if (!bHasOtherSlowEffect)
				{
					IMovable::Execute_StopSlow(InMovableActor);
				}
				SlowedActors.RemoveAt(i);
			}
			return true;
		}
	}
	
	return false;
}

bool APhysicsManager::StopSlowActorByID(int32 InSlowActorID, bool bForceStop)
{
	if (!SlowedActors.IsValidIndex(InSlowActorID))
		return false;

	if (bForceStop || SlowedActors[InSlowActorID].SlowTime <= 0 || SlowedActors[InSlowActorID].SlowPercent <= 0)
	{
		bool bHasOtherSlowEffect = false;
		for (int i = 0; i < IceSlowedActors.Num(); i++)
		{
			if (IceSlowedActors[i].MovableActor == SlowedActors[InSlowActorID].MovableActor)
			{
				bHasOtherSlowEffect = true;
				break;
			}
		}
		
		if (!bHasOtherSlowEffect)
		{
			IMovable::Execute_StopSlow(SlowedActors[InSlowActorID].MovableActor);
		}
		SlowedActors.RemoveAt(InSlowActorID);
		return true;
	}
	return false;
}

void APhysicsManager::StartIceSlowActor(UObject* InMovableActor, float InSlowPercent)
{
	if (!InMovableActor)
		return;
	
	for (int i = 0; i < IceSlowedActors.Num(); i++)
	{
		if (IceSlowedActors[i].MovableActor == InMovableActor)
		{
			IceSlowedActors[i].AssignCount++;
			IceSlowedActors[i].SlowPercent = FMath::Max(IceSlowedActors[i].SlowPercent, InSlowPercent);
			
			IMovable::Execute_StartSlow(InMovableActor, IceSlowedActors[i].SlowPercent);
			
			return;
		}
	}
	
	FIceSlowData NewSlowData;
	NewSlowData.MovableActor = InMovableActor;
	NewSlowData.SlowPercent = InSlowPercent;
	NewSlowData.AssignCount = 1;
	IMovable::Execute_StartSlow(InMovableActor, InSlowPercent);
	IceSlowedActors.Add(NewSlowData);
}

bool APhysicsManager::StopIceSlowActor(UObject* InMovableActor, float InSlowPercent,
	bool bForceStop)
{
	if (!InMovableActor)
		return false;

	for (int i = 0; i < IceSlowedActors.Num(); i++)
	{
		if (IceSlowedActors[i].MovableActor == InMovableActor)
		{
			IceSlowedActors[i].AssignCount--;
			IceSlowedActors[i].SlowPercent -= InSlowPercent;
			if (bForceStop || IceSlowedActors[i].AssignCount <= 0 || IceSlowedActors[i].SlowPercent <= 0)
			{
				bool bHasOtherSlowEffect = false;
				for (int j = 0; j < SlowedActors.Num(); j++)
				{
					if (SlowedActors[j].MovableActor == InMovableActor)
					{
						bHasOtherSlowEffect = true;
						break;
					}
				}
				if (!bHasOtherSlowEffect)
				{
					IMovable::Execute_StopSlow(InMovableActor);
				}
				IceSlowedActors.RemoveAt(i);
			}
			return true;
		}
	}

	return false;
}

void APhysicsManager::StartStunActor(UObject* InMovableActor, float InStunTime)
{
	if (!InMovableActor)
		return;

	for (int i = 0; i < StunnedActors.Num(); i++)
	{
		if (StunnedActors[i].MovableActor == InMovableActor)
		{
			StunnedActors[i].StunTime += InStunTime;
			return;
		}
	}

	FStunData NewStunData;
	NewStunData.MovableActor = InMovableActor;
	NewStunData.StunTime = InStunTime;
	IMovable::Execute_StartStun(InMovableActor);
	StunnedActors.Add(NewStunData);
}

bool APhysicsManager::StopStunActor(UObject* InMovableActor, bool bForceStop)
{
	if (!InMovableActor)
		return false;

	for (int i = 0; i < StunnedActors.Num(); i++)
	{
		if (StunnedActors[i].MovableActor == InMovableActor)
		{
			if (bForceStop || StunnedActors[i].StunTime <= 0)
			{
				IMovable::Execute_StopStun(InMovableActor);
				StunnedActors.RemoveAt(i);
			}
			return true;
		}
	}
	return false;
}

bool APhysicsManager::StopStunActorByID(int32 InStunActorID, bool bForceStop)
{
	if (!StunnedActors.IsValidIndex(InStunActorID))
		return false;

	if (bForceStop || StunnedActors[InStunActorID].StunTime <= 0)
	{
		IMovable::Execute_StopStun(StunnedActors[InStunActorID].MovableActor);
		StunnedActors.RemoveAt(InStunActorID);
		return true;
	}
	
	return false;
}

void APhysicsManager::ThrowActor(UObject* InThrowableActor, UPrimitiveComponent* ThrowPrimitiveComponent, const FVector& InThrowNormal, const float InThrowForce)
{
	if (!InThrowableActor)
		return;

	IThrowable::Execute_AddThrowImpulse(InThrowableActor, ThrowPrimitiveComponent, InThrowNormal * InThrowForce);
}

void APhysicsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetFollowMap.IsEmpty())
	{
		for (int i = TargetFollowMap.Num() - 1; i >= 0; i--)
		{
			if (!IsValid(TargetFollowMap[i].FollowActor) || !IsValid(TargetFollowMap[i].TargetActor))
			{
				TargetFollowMap.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Force remove"));
				continue;
			};

			AActor* FollowActorRef = IFollow::Execute_GetFollowActor(TargetFollowMap[i].FollowActor);

			if (!IsValid(FollowActorRef))
			{
				TargetFollowMap.RemoveAt(i);
				UE_LOG(LogTemp, Display, TEXT("Force remove"));
				continue;
			}

			//Right now just simple interpolation, later will include gravitation and physics in computation etc.
			FVector ActorLocation = FollowActorRef->GetActorLocation();
			FVector TargetLocation = ITarget::Execute_GetTargetLocation(TargetFollowMap[i].TargetActor);
			FVector GoalLocation = UKismetMathLibrary::VInterpTo(ActorLocation, TargetLocation, DeltaTime, TargetFollowInterpSpeed);
			FollowActorRef->SetActorLocation(GoalLocation);
		}
	}

	if (!SlowedActors.IsEmpty())
	{
		for (int i = SlowedActors.Num() - 1; i >= 0; i--)
		{
			SlowedActors[i].SlowTime -= DeltaTime;
			if (SlowedActors[i].SlowTime <= 0)
			{
				StopSlowActorByID(i, true);
			}
		}
	}

	if (!StunnedActors.IsEmpty())
	{
		for (int i = StunnedActors.Num() - 1; i >= 0; i--)
		{
			StunnedActors[i].StunTime -= DeltaTime;
			if (StunnedActors[i].StunTime <= 0)
			{
				StopStunActorByID(i, true);
			}
		}
	}
}
