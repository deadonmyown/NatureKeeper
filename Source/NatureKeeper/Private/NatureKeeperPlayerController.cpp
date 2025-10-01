// Copyright Epic Games, Inc. All Rights Reserved.

#include "NatureKeeper/Public/NatureKeeperPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NatureKeeper/Public/NatureKeeperCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "FocusComponent.h"
#include "IsometricCell.h"
#include "NatureKeeperUtils.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "TargetSystem/TargetComponent.h"
#include "TargetSystem/TargetStrategy.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ANatureKeeperPlayerController::ANatureKeeperPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FollowTime = 0.f;
}

void ANatureKeeperPlayerController::BeginPlay()
{
	Super::BeginPlay();

	NatureKeeperCharacter = Cast<ANatureKeeperCharacter>(GetCharacter());

	GetWorld()->GetTimerManager().SetTimer(TraceUpdateTimerHandle, this, &ANatureKeeperPlayerController::UpdateTrace, TraceUpdateTime);
}

void ANatureKeeperPlayerController::UpdateTrace()
{
	FHitResult Hit;
	
	bool bIsFocus = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bIsFocus)
	{
		float FocusDistanceToPlayer = FVector::Distance(Hit.Location, NatureKeeperCharacter->GetActorLocation());
		UPrimitiveComponent* FocusedComponent = Hit.GetComponent();
		AActor* FocusedActor = Hit.GetActor();
		NatureKeeperCharacter->GetFocusComponent()->UpdateFocus(bIsFocus, FocusDistanceToPlayer, FocusedComponent, FocusedActor);
	}
	else
	{
		NatureKeeperCharacter->GetFocusComponent()->ClearFocus();
	}
}

void ANatureKeeperPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnSetDestinationReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANatureKeeperPlayerController::OnInputStarted()
{

	if (NatureKeeperCharacter->GetTargetComponent()->GetTargetStrategy() && NatureKeeperCharacter->GetTargetComponent()->GetTargetStrategy()->GetIsTargeting())
		return;

	UpdateTrace();

	if (NatureKeeperCharacter->GetFocusComponent()->bIsFocus)
	{
		if (NatureKeeperCharacter->GetFocusComponent()->FocusedActor->Implements<UInteractiveActorInterface>())
		{
			IInteractiveActorInterface::Execute_StartInteract(NatureKeeperCharacter->GetFocusComponent()->FocusedActor, GetCharacter());
		}
	}
}

// Triggered every frame when the input is held down
void ANatureKeeperPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
}

void ANatureKeeperPlayerController::OnSetDestinationReleased()
{
	UpdateTrace();
	
	if (NatureKeeperCharacter->GetFocusComponent()->bIsFocus)
	{
		if (NatureKeeperCharacter->GetFocusComponent()->FocusedActor->Implements<UInteractiveActorInterface>())
		{
			if (IInteractiveActorInterface::Execute_StopInteract(NatureKeeperCharacter->GetFocusComponent()->FocusedActor, GetCharacter()))
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor,
					NatureKeeperCharacter->GetFocusComponent()->FocusedActor->GetActorLocation(),
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);
			}
		}
	}

	FollowTime = 0.f;
}