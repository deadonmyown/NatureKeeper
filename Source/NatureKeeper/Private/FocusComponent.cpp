#include "FocusComponent.h"

#include "NatureKeeperCharacter.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "Kismet/GameplayStatics.h"

UFocusComponent::UFocusComponent()
{
	PlayerController = nullptr;
	FocusDistanceToActor = 0.0f;
	FocusedComponent = nullptr;
	FocusedActor = nullptr;
}

void UFocusComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<ANatureKeeperCharacter>(GetOwner());
	
	if (PlayerRef)
		PlayerController = Cast<ANatureKeeperPlayerController>(PlayerRef->GetController());
	
	if (PlayerController)
		GetWorld()->GetTimerManager().SetTimer(TraceUpdateTimerHandle, this, &UFocusComponent::UpdateTrace, TraceUpdateTime);
}

void UFocusComponent::UpdateTrace()
{
	FHitResult Hit;
	
	bool bIsHit = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bIsHit)
	{
		float Distance = FVector::Distance(Hit.Location, GetOwner()->GetActorLocation());
		FVector HitLoc = Hit.Location;
		UPrimitiveComponent* HitComponent = Hit.GetComponent();
		AActor* HitActor = Hit.GetActor();
		UpdateFocus(bIsHit, Distance, HitLoc, HitComponent, HitActor);
	}
	else
	{
		ClearFocus();
	}
}

USceneComponent* UFocusComponent::GetPlayerMuzzleComponent_Implementation()
{
	if (PlayerRef)
		return PlayerRef->GetMuzzleComponent();

	return GetOwner()->GetRootComponent();
}

void UFocusComponent::GetPlayerCursorLookAtNormalized_Implementation(FVector& OutputDirectionNormalized, FVector& OutputWorldLocation)
{
	FVector CameraDir;
	if (PlayerController->DeprojectMousePositionToWorld(OutputWorldLocation, CameraDir))
	{
		const FVector ActorLoc = GetOwner()->GetActorLocation();
		if (FMath::Abs(CameraDir.Z) > KINDA_SMALL_NUMBER)
		{
			float T = (ActorLoc.Z - OutputWorldLocation.Z) / CameraDir.Z;
			FVector HitPoint = OutputWorldLocation + CameraDir * T;

			OutputDirectionNormalized = HitPoint - ActorLoc;
			OutputDirectionNormalized.Z = 0.0f;
			OutputDirectionNormalized = OutputDirectionNormalized.GetSafeNormal();
			
		}
		else
		{
			OutputDirectionNormalized = CameraDir.GetSafeNormal();
		}
	}
}

void UFocusComponent::GetPlayerLookAtNormalized_Implementation(FVector& OutputDirection)
{
	OutputDirection = GetOwner()->GetActorForwardVector();
}

void UFocusComponent::GetPlayerLookAtNormalizedLocation_Implementation(FVector& OutputResult)
{
	OutputResult = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector();
}

void UFocusComponent::UpdateFocus_Implementation(bool bInIsFocus, float InDistanceToPlayer, FVector InFocusHitLocation,
                                                 UPrimitiveComponent* InFocusComponent, AActor* InFocusActor)
{
	if (!bInIsFocus)
	{
		ClearFocus();
		return;
	}

	bIsFocus = true;
	//DO SOMETHING LIKE UI OR VISUAL STUFF
	if (FocusedActor && FocusedActor != InFocusActor)
	{
		if (FocusedActor->Implements<UInteractiveActorInterface>())
		{
			IInteractiveActorInterface::Execute_StopFocus(FocusedActor, GetOwner());
		}
	}
	
	FocusDistanceToActor = InDistanceToPlayer;
	FocusHitCacheLocation = InFocusHitLocation;
	FocusedComponent = InFocusComponent;
	FocusedActor = InFocusActor;

	if (FocusedActor->Implements<UInteractiveActorInterface>())
	{
		IInteractiveActorInterface::Execute_StartFocus(FocusedActor, GetOwner());
	}
}

void UFocusComponent::ClearFocus_Implementation()
{
	bIsFocus = false;
	FocusDistanceToActor = 0.f;
	FocusHitCacheLocation = FVector::ZeroVector;
	FocusedComponent = nullptr;
	FocusedActor = nullptr;
}
