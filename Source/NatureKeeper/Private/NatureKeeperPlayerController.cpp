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
#include "Effects/Ability.h"
#include "Effects/AbilityComponent.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "TargetSystem/TargetComponent.h"
#include "TargetSystem/TargetStrategy.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ANatureKeeperPlayerController::ANatureKeeperPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	MainTriggerTime = 0.0f;
	SecondaryTriggerTime = 0.0f;
	bIsInteract = false;
}

void ANatureKeeperPlayerController::StartLookAtCursor()
{
	bLookAtCursor = true;
}

void ANatureKeeperPlayerController::StopLookAtCursor()
{
	bLookAtCursor = false;
}

void ANatureKeeperPlayerController::BeginPlay()
{
	Super::BeginPlay();

	NatureKeeperCharacter = Cast<ANatureKeeperCharacter>(GetCharacter());
	if (NatureKeeperCharacter)
	{
		PlayerFocusComponent = NatureKeeperCharacter->GetFocusComponent();
		PlayerTargetComponent = NatureKeeperCharacter->GetTargetComponent();
		PlayerAbilityComponent = NatureKeeperCharacter->GetAbilityComponent();
	}
}

void ANatureKeeperPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bLookAtCursor && !bIsInteract)
	{
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn != nullptr)
		{
			FVector WorldDirectionNormalized;
			FVector WorldLocation;
			FVector WorldLocationNorm;
			PlayerFocusComponent->GetPlayerCursorLookAtNormalized(WorldDirectionNormalized, WorldLocation, WorldLocationNorm);

			if (WorldDirectionNormalized.IsNearlyZero()) return;

			FRotator TargetRot = WorldDirectionNormalized.Rotation();
			TargetRot.Pitch = 0.0f;
			TargetRot.Roll = 0.0f;

			FRotator NewRot = FMath::RInterpTo(ControlledPawn->GetActorRotation(), TargetRot, DeltaSeconds, LookAtCursorRotationSpeed);

			ControlledPawn->SetActorRotation(NewRot);
		}
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
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnSecondaryInputStarted);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnSecondaryInputTriggered);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnSecondaryInputStopped);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnSecondaryInputStopped);

		for (int i = 0; i < AbilitiesActions.Num(); i++)
		{
			if (!AbilitiesActions[i]) continue;
			EnhancedInputComponent->BindAction(AbilitiesActions[i], ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnAbilityAction);
		}
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANatureKeeperPlayerController::OnInputStarted()
{
	/*if (PlayerTargetComponent->GetTargetStrategy() && PlayerTargetComponent->GetTargetStrategy()->GetIsTargeting())
	{
		OnPlayerMainClickStarted.Broadcast();
		return;
	}*/

	StopMovement();
	
	PlayerFocusComponent->UpdateTrace();

	if (PlayerFocusComponent->bIsFocus)
	{
		if (PlayerFocusComponent->FocusedActor->Implements<UInteractiveActorInterface>())
		{
			if (IInteractiveActorInterface::Execute_StartInteract(PlayerFocusComponent->FocusedActor, GetCharacter()))
			{
				bIsInteract = true;
			}
		}
	}

	if (OnPlayerMainClickStarted.IsBound())
		OnPlayerMainClickStarted.Broadcast();
}

// Triggered every frame when the input is held down
void ANatureKeeperPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	MainTriggerTime += GetWorld()->GetDeltaSeconds();
	
	/*if (PlayerTargetComponent->GetTargetStrategy() && PlayerTargetComponent->GetTargetStrategy()->GetIsTargeting())
	{
		OnPlayerMainClickTriggered.Broadcast();
		return;
	}*/

	/*if (!bIsInteract)
	{*/
		// Move towards mouse pointer
		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn != nullptr)
		{
			FVector WorldDirectionNormalized;
			FVector WorldLocation;
			FVector WorldLocationNorm;
			PlayerFocusComponent->GetPlayerCursorLookAtNormalized(WorldDirectionNormalized, WorldLocation, WorldLocationNorm);
			ControlledPawn->AddMovementInput(WorldDirectionNormalized, 1.0, false);
		}
	//}

	if (OnPlayerMainClickTriggered.IsBound())
		OnPlayerMainClickTriggered.Broadcast(MainTriggerTime);
}

void ANatureKeeperPlayerController::OnSetDestinationReleased()
{
	/*if (PlayerTargetComponent->GetTargetStrategy() && PlayerTargetComponent->GetTargetStrategy()->GetIsTargeting())
	{
		TriggerTime = 0.f;
		bIsInteract = false;
		OnPlayerMainClickStopped.Broadcast();
		return;
	}*/
	
	PlayerFocusComponent->UpdateTrace();

	
	if (PlayerFocusComponent->bIsFocus)
	{
		if (bIsInteract && PlayerFocusComponent->FocusedActor->Implements<UInteractiveActorInterface>())
		{
			IInteractiveActorInterface::Execute_StopInteract(PlayerFocusComponent->FocusedActor, GetCharacter());
				
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor,
				PlayerFocusComponent->FocusedActor->GetActorLocation(),
				FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
				true, true, ENCPoolMethod::None, true);
		}
		/*else
		{
			// If it was a short press
			if (MainTriggerTime <= ShortPressThreshold)
			{
				// We move there and spawn some particles
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PlayerFocusComponent->FocusHitCacheLocation);

				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor,
					PlayerFocusComponent->FocusHitCacheLocation,
					FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
					true, true, ENCPoolMethod::None, true);
			}
		}*/
	}

	if(OnPlayerMainClickStopped.IsBound())
		OnPlayerMainClickStopped.Broadcast(MainTriggerTime);
	
	bIsInteract = false;
	MainTriggerTime = 0.f;

}

void ANatureKeeperPlayerController::OnSecondaryInputStarted()
{
	//StartLookAtCursor();
	if (OnPlayerSecondaryClickStarted.IsBound())
		OnPlayerSecondaryClickStarted.Broadcast();
}

void ANatureKeeperPlayerController::OnSecondaryInputTriggered()
{
	SecondaryTriggerTime += GetWorld()->GetDeltaSeconds();
	
	if (OnPlayerSecondaryClickTriggered.IsBound())
		OnPlayerSecondaryClickTriggered.Broadcast(SecondaryTriggerTime);
}

void ANatureKeeperPlayerController::OnSecondaryInputStopped()
{
	//StopLookAtCursor();
	if (OnPlayerSecondaryClickStopped.IsBound())
		OnPlayerSecondaryClickStopped.Broadcast(SecondaryTriggerTime);

	SecondaryTriggerTime = 0.0f;
}

void ANatureKeeperPlayerController::OnAbilityAction(const FInputActionInstance& Instance)
{
	const UInputAction* SourceAction = Instance.GetSourceAction();
	if (!SourceAction) return;

	const int32 Index = AbilitiesActions.IndexOfByKey(SourceAction);

	TArray<UAbility*> Abilities = PlayerAbilityComponent->GetAbilities();
	if (!Abilities.IsValidIndex(Index))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability index not valid for action %s"), *SourceAction->GetName());
		return;
	}

	UAbility* Ability = Abilities[Index];
	if (!Ability)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability is null at index %d"), Index);
		return;
	}

	Ability->Target(PlayerTargetComponent);
}
