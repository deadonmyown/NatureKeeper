#include "InteractionSystem/InteractiveActor.h"

AInteractiveActor::AInteractiveActor()
{
}

bool AInteractiveActor::StartInteract_Implementation(ACharacter* InteractionInvoker)
{
	return true;
}

bool AInteractiveActor::StopInteract_Implementation(ACharacter* InteractionInvoker)
{
	return true;
}