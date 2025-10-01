#include "FocusComponent.h"

#include "Interfaces/InteractiveActorInterface.h"

UFocusComponent::UFocusComponent()
{
}

void UFocusComponent::BeginPlay()
{
	Super::BeginPlay();

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
	
	FocusDistanceToPlayer = InDistanceToPlayer;
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
	FocusDistanceToPlayer = 0.f;
	FocusedComponent = nullptr;
	FocusedActor = nullptr;
}
