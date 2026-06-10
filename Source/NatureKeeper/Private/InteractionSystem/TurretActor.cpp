#include "InteractionSystem/TurretActor.h"

#include "Components/SphereComponent.h"


ATurretActor::ATurretActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetSphereRadius(1000.0f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurretActor::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATurretActor::OnEndOverlap);
}

void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurretActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ActorsInRadius.Contains(OtherActor))
		return;
	
	if (OtherActor->Implements<UDamageable>())
	{
		ActorsInRadius.Add(OtherActor);
		OtherActor->OnDestroyed.AddDynamic(this, &ATurretActor::OnOtherActorDestroyed);
	}
}

void ATurretActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor))
		return;

	if (ActorsInRadius.Contains(OtherActor))
	{
		OtherActor->OnDestroyed.RemoveDynamic(this, &ATurretActor::OnOtherActorDestroyed);
		ActorsInRadius.Remove(OtherActor);
	}
}

void ATurretActor::OnOtherActorDestroyed(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
		return;

	if (ActorsInRadius.Contains(OtherActor))
	{
		ActorsInRadius.Remove(OtherActor);
	}
}

void ATurretActor::SortTurretData()
{
	ActorsInRadius.RemoveAll([](const FTurretData& Data) {return !IsValid(Data.TurretActor); });
	
	ActorsInRadius.Sort([this](const FTurretData& A, const FTurretData& B)
	{
		if (!A.TurretActor) return false;
		if (!B.TurretActor) return true;

		if (A.bInFOV != B.bInFOV)
		{
			return A.bInFOV > B.bInFOV;
		}

		float DistA = GetDistanceTo(A.TurretActor);
		float DistB = GetDistanceTo(B.TurretActor);

		return DistA < DistB;
	});
}


void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActorsInRadius.IsEmpty())
		return;

	for (int i = 0; i < ActorsInRadius.Num(); i++)
	{
		FVector ActorInRadiusLoc = ActorsInRadius[i].TurretActor->GetActorLocation();
		FVector TurretForwardVector = GetActorForwardVector();
		FVector VectorToActorInRadius = (ActorInRadiusLoc - GetActorLocation()).GetSafeNormal();
		
		if (ActorsInRadius[i].bInFOV)
		{
			if (FVector::DotProduct(TurretForwardVector, VectorToActorInRadius) > FOVAngle)
			{
				ActorsInRadius[i].bInFOV = false;
				continue;
			}

			//Sort only if we have actors in fov to detect nearest, in other case there is no reason in this costly operation
			if (LastSortTime >= SortPeriodInSec)
			{
				SortTurretData();
				LastSortTime = 0.0f;
			}
			else
			{
				LastSortTime += DeltaTime;
			}

			const FTurretData& TurretData = ActorsInRadius[i];
			//TODO: Apply ability
		}
		else
		{
			if (FVector::DotProduct(TurretForwardVector, VectorToActorInRadius) <= FOVAngle)
			{
				ActorsInRadius[i].bInFOV = true;
				continue;
			}
		}
	}
}

