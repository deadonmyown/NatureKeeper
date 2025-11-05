#include "InteractionSystem/InteractiveCharacter.h"


AInteractiveCharacter::AInteractiveCharacter()
{
}

void AInteractiveCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AInteractiveCharacter::StartInteract_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool AInteractiveCharacter::StopInteract_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool AInteractiveCharacter::StartFocus_Implementation(AActor* InteractionInvoker)
{
	return true;
}

bool AInteractiveCharacter::StopFocus_Implementation(AActor* InteractionInvoker)
{
	return true;
}
