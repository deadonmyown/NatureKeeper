// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "InteractiveCharacter.generated.h"

UCLASS()
class NATUREKEEPER_API AInteractiveCharacter : public ACharacter, public IInteractiveActorInterface
{
	GENERATED_BODY()

public:
	AInteractiveCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual bool StartInteract_Implementation(AActor* InteractionInvoker) override;
	virtual bool StopInteract_Implementation(AActor* InteractionInvoker) override;
	virtual bool StartFocus_Implementation(AActor* InteractionInvoker) override;
	virtual bool StopFocus_Implementation(AActor* InteractionInvoker) override;
};
