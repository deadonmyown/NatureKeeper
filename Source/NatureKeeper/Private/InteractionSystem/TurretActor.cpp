#include "InteractionSystem/TurretActor.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ResourceSystem/HealthComponent.h"
#include "TargetSystem/TargetComponent.h"


ATurretActor::ATurretActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetSphereRadius(1000.0f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurretActor::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATurretActor::OnEndOverlap);

	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");
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
	
	if (OtherActor->Implements<UDamageable>() && DamageableTypesTarget.Contains(IDamageable::Execute_GetDamageableType(OtherActor)))
	{
		ActorsInRadius.Add(OtherActor);
		OtherActor->OnDestroyed.AddDynamic(this, &ATurretActor::OnOtherActorDestroyed);

		SortTurretData();
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

		SortTurretData();
	}
}

void ATurretActor::OnOtherActorDestroyed(AActor* OtherActor)
{
	if (!IsValid(OtherActor))
		return;

	if (ActorsInRadius.Contains(OtherActor))
	{
		ActorsInRadius.Remove(OtherActor);

		SortTurretData();
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

	if (ActorsInRadius.IsEmpty() || HealthComponent->GetResourceValue() == HealthComponent->GetMinResourceValue())
	{
		if (TargetComponent->IsTargeting())
		{
			TargetComponent->CancelTargetStrategy();
		}
		return;
	}

	bool bFoundActorInFOV = false;
	for (int i = 0; i < ActorsInRadius.Num(); i++)
	{
		FVector ActorInRadiusLoc = ActorsInRadius[i].TurretActor->GetActorLocation();
		FVector TurretForwardVector = GetActorForwardVector();
		FVector VectorToActorInRadius = (ActorInRadiusLoc - GetActorLocation()).GetSafeNormal();
		
		if (ActorsInRadius[i].bInFOV)
		{
			if (FVector::DotProduct(TurretForwardVector, VectorToActorInRadius) < FOVAngle)
			{
				ActorsInRadius[i].bInFOV = false;
				SortTurretData();
				return;
			}

			bFoundActorInFOV = true;
		}
		else
		{
			if (FVector::DotProduct(TurretForwardVector, VectorToActorInRadius) >= FOVAngle)
			{
				ActorsInRadius[i].bInFOV = true;
				SortTurretData();
				return;
			}
		}
	}
	
	if (bFoundActorInFOV)
	{
		const FTurretData& TurretData = ActorsInRadius[0];

		FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TurretData.TurretActor->GetActorLocation());

		SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), TargetRotator, DeltaTime, RotationToTargetSpeed));
		if (!TargetComponent->IsTargeting())
		{
			TargetComponent->AddAbilityEffectByIndex(0);
			TargetComponent->StartTargetStrategy();
		}
	}
	else if (!bFoundActorInFOV && TargetComponent->IsTargeting())
	{
		TargetComponent->CancelTargetStrategy();
	}
}

