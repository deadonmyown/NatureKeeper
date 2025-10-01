#include "InteractionSystem/InteractiveActor.h"

AInteractiveActor::AInteractiveActor()
{
}

bool AInteractiveActor::StartInteract_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool AInteractiveActor::StopInteract_Implementation(AActor* InteractionInvoker)
{
	return true;
}