#include "FocusComponent.h"

#include "NatureKeeperCharacter.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "Kismet/GameplayStatics.h"

UFocusComponent::UFocusComponent()
{
	PlayerController = nullptr;
	CursorFocusDistanceToActor = 0.0f;
	CursorFocusedComponent = nullptr;
	CursorFocusedActor = nullptr;
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
	FHitResult CursorHit;
	
	bool bIsCursorHit = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, CursorHit);

	if (bIsCursorHit)
	{
		float Distance = FVector::Distance(CursorHit.Location, GetOwner()->GetActorLocation());
		FVector HitLoc = CursorHit.Location;
		UPrimitiveComponent* HitComponent = CursorHit.GetComponent();
		AActor* HitActor = CursorHit.GetActor();
		UpdateCursorFocus(bIsCursorHit, Distance, HitLoc, HitComponent, HitActor);
	}
	else
	{
		ClearCursorFocus();
	}

	FVector PlayerLookVector;
	GetPlayerLookAtNormalized(PlayerLookVector);
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + PlayerLookVector * PlayerTraceDistance;
	FHitResult PlayerHit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	Params.bTraceComplex = false;

	bool bIsPlayerHit = GetWorld()->LineTraceSingleByChannel(
		PlayerHit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	if (bIsPlayerHit)
	{
		float Distance = FVector::Distance(PlayerHit.Location, GetOwner()->GetActorLocation());
		FVector HitLoc = PlayerHit.Location;
		UPrimitiveComponent* HitComponent = PlayerHit.GetComponent();
		AActor* HitActor = PlayerHit.GetActor();
		UpdatePlayerFocus(bIsPlayerHit, Distance, HitLoc, HitComponent, HitActor);
	}
	else
	{
		ClearPlayerFocus();
	}
	
}

FVector UFocusComponent::GetTargetLocation_Implementation()
{
	FVector WorldDirectionNormalized;
	FVector WorldLocation;
	FVector WorldLocationNorm;
	GetPlayerCursorLookAtNormalized(WorldDirectionNormalized, WorldLocation, WorldLocationNorm);
	return WorldLocationNorm;
}

FRotator UFocusComponent::GetTargetRotation_Implementation()
{
	return GetOwner()->GetActorRotation();
}

USceneComponent* UFocusComponent::GetPlayerMuzzleComponent_Implementation()
{
	if (PlayerRef)
		return PlayerRef->GetMuzzleComponent();

	return GetOwner()->GetRootComponent();
}

void UFocusComponent::GetPlayerCursorLookAtNormalized_Implementation(FVector& OutputDirectionNormalized, FVector& OutputWorldLocation, FVector& OutputNormalizedWorldLocation)
{
	FVector CameraDir;
	OutputDirectionNormalized = GetOwner()->GetActorForwardVector();
	OutputWorldLocation = GetOwner()->GetActorLocation();
	OutputNormalizedWorldLocation = OutputWorldLocation;
	if (PlayerController->DeprojectMousePositionToWorld(OutputWorldLocation, CameraDir))
	{
		const FVector ActorLoc = GetOwner()->GetActorLocation();
		if (FMath::Abs(CameraDir.Z) > KINDA_SMALL_NUMBER)
		{
			float T = (ActorLoc.Z - OutputWorldLocation.Z) / CameraDir.Z;
			OutputNormalizedWorldLocation = OutputWorldLocation + CameraDir * T;

			OutputDirectionNormalized = OutputNormalizedWorldLocation - ActorLoc;
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

void UFocusComponent::UpdateCursorFocus_Implementation(bool bInIsFocus, float InDistanceToActor, FVector InFocusHitLocation,
                                                 UPrimitiveComponent* InFocusComponent, AActor* InFocusActor)
{
	if (!bInIsFocus)
	{
		ClearCursorFocus();
		return;
	}

	bIsCursorFocus = true;
	//DO SOMETHING LIKE UI OR VISUAL STUFF
	if (CursorFocusedActor && CursorFocusedActor != InFocusActor)
	{
		if (CursorFocusedActor->Implements<UInteractiveActorInterface>())
		{
			IInteractiveActorInterface::Execute_StopCursorFocus(CursorFocusedActor, GetOwner());
		}
	}
	
	CursorFocusDistanceToActor = InDistanceToActor;
	CursorFocusHitCacheLocation = InFocusHitLocation;
	CursorFocusedComponent = InFocusComponent;
	CursorFocusedActor = InFocusActor;

	if (CursorFocusedActor->Implements<UInteractiveActorInterface>())
	{
		IInteractiveActorInterface::Execute_StartCursorFocus(CursorFocusedActor, GetOwner());
	}
}

void UFocusComponent::ClearCursorFocus_Implementation()
{
	if (CursorFocusedActor && CursorFocusedActor->Implements<UInteractiveActorInterface>())
	{
		IInteractiveActorInterface::Execute_StopCursorFocus(CursorFocusedActor, GetOwner());
	}
	
	bIsCursorFocus = false;
	CursorFocusDistanceToActor = 0.f;
	CursorFocusHitCacheLocation = FVector::ZeroVector;
	CursorFocusedComponent = nullptr;
	CursorFocusedActor = nullptr;
}

void UFocusComponent::UpdatePlayerFocus_Implementation(bool bInIsFocus, float InDistanceToActor,
													   FVector InFocusHitLocation, UPrimitiveComponent* InFocusComponent, AActor* InFocusActor)
{
	if (!bInIsFocus)
	{
		ClearPlayerFocus();
		return;
	}

	bIsPlayerFocus = true;
	//DO SOMETHING LIKE UI OR VISUAL STUFF
	if (PlayerFocusedActor && PlayerFocusedActor != InFocusActor)
	{
		if (PlayerFocusedActor->Implements<UInteractiveActorInterface>())
		{
			IInteractiveActorInterface::Execute_StopPlayerFocus(PlayerFocusedActor, GetOwner());
		}
	}
	
	PlayerFocusDistanceToActor = InDistanceToActor;
	PlayerFocusHitCacheLocation = InFocusHitLocation;
	PlayerFocusedComponent = InFocusComponent;
	PlayerFocusedActor = InFocusActor;

	if (PlayerFocusedActor->Implements<UInteractiveActorInterface>())
	{
		IInteractiveActorInterface::Execute_StartPlayerFocus(PlayerFocusedActor, GetOwner());
	}
}

void UFocusComponent::ClearPlayerFocus_Implementation()
{
	if (PlayerFocusedActor && PlayerFocusedActor->Implements<UInteractiveActorInterface>())
	{
		IInteractiveActorInterface::Execute_StopPlayerFocus(PlayerFocusedActor, GetOwner());
	}
	
	bIsPlayerFocus = false;
	PlayerFocusDistanceToActor = 0.f;
	PlayerFocusHitCacheLocation = FVector::ZeroVector;
	PlayerFocusedComponent = nullptr;
	PlayerFocusedActor = nullptr;
}