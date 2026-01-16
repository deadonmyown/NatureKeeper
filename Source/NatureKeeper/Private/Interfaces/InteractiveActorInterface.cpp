// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractiveActorInterface.h"


bool IInteractiveActorInterface::StartInteract_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool IInteractiveActorInterface::StopInteract_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool IInteractiveActorInterface::StartCursorFocus_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool IInteractiveActorInterface::StopCursorFocus_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool IInteractiveActorInterface::StartPlayerFocus_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool IInteractiveActorInterface::StopPlayerFocus_Implementation(AActor* InteractionInvoker)
{
	return true;
}
