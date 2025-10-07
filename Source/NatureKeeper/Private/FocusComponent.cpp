#include "FocusComponent.h"

#include "NatureKeeperCharacter.h"
#include "Interfaces/InteractiveActorInterface.h"

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

	PlayerController = Cast<APlayerController>(Cast<ACharacter>(GetOwner())->GetController());
	
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
		UPrimitiveComponent* HitComponent = Hit.GetComponent();
		AActor* HitActor = Hit.GetActor();
		UpdateFocus(bIsHit, Distance, HitComponent, HitActor);
	}
	else
	{
		ClearFocus();
	}
}

void UFocusComponent::UpdateFocus_Implementation(bool bInIsFocus, float InDistanceToPlayer,
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
	FocusedComponent = nullptr;
	FocusedActor = nullptr;
}
