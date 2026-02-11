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
#include "Camera/CameraComponent.h"
#include "Effects/Ability.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/InteractiveActorInterface.h"
#include "TargetSystem/FocusHoldTargetStrategy.h"
#include "TargetSystem/SelfTargetStrategy.h"
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
		// Setup keyboard input events
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnMove);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnStopJumping);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnStartInteraction);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnEndInteraction);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnEndInteraction);
		// Setup mouse input events
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(PrimaryClickAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnSecondaryInputStarted);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnSecondaryInputTriggered);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnSecondaryInputStopped);
		EnhancedInputComponent->BindAction(SecondaryClickAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnSecondaryInputStopped);
		EnhancedInputComponent->BindAction(ThirdClickAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnThirdInputStarted);
		EnhancedInputComponent->BindAction(ThirdClickAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnThirdInputTriggered);
		EnhancedInputComponent->BindAction(ThirdClickAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnThirdInputStopped);
		EnhancedInputComponent->BindAction(ThirdClickAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnThirdInputStopped);

		for (int i = 0; i < EffectsActions.Num(); i++)
		{
			if (!EffectsActions[i]) continue;
			EnhancedInputComponent->BindAction(EffectsActions[i], ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnEffectActions);
		}

		for (int i = 0; i < EffectTargetStrategiesActions.Num(); i++)
		{
			if (!EffectTargetStrategiesActions[i]) continue;
			EnhancedInputComponent
			->BindAction(EffectTargetStrategiesActions[i], ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnEffectTargetStrategiesActions);
		}
		
		EnhancedInputComponent->BindAction(EffectClearAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnEffectClear);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANatureKeeperPlayerController::OnInputStarted()
{
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
	{
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
	}*/

	if (OnPlayerMainClickTriggered.IsBound())
		OnPlayerMainClickTriggered.Broadcast(MainTriggerTime);
}

void ANatureKeeperPlayerController::OnSetDestinationReleased()
{
	if(OnPlayerMainClickStopped.IsBound())
		OnPlayerMainClickStopped.Broadcast(MainTriggerTime);
	
	MainTriggerTime = 0.f;
}

void ANatureKeeperPlayerController::OnSecondaryInputStarted()
{
	OnEffectTargetStrategiesActionsByClass(UFocusHoldTargetStrategy::StaticClass());
	
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
	if (OnPlayerSecondaryClickStopped.IsBound())
		OnPlayerSecondaryClickStopped.Broadcast(SecondaryTriggerTime);

	SecondaryTriggerTime = 0.0f;
}

void ANatureKeeperPlayerController::OnThirdInputStarted()
{
	OnEffectTargetStrategiesActionsByClass(USelfTargetStrategy::StaticClass());
	
	if (OnPlayerThirdClickStarted.IsBound())
		OnPlayerThirdClickStarted.Broadcast();
}

void ANatureKeeperPlayerController::OnThirdInputTriggered()
{
	ThirdTriggerTime += GetWorld()->GetDeltaSeconds();
	
	if (OnPlayerThirdClickTriggered.IsBound())
		OnPlayerThirdClickTriggered.Broadcast(ThirdTriggerTime);
}

void ANatureKeeperPlayerController::OnThirdInputStopped()
{
	if (OnPlayerThirdClickStopped.IsBound())
		OnPlayerThirdClickStopped.Broadcast(ThirdTriggerTime);

	ThirdTriggerTime = 0.0f;
}

void ANatureKeeperPlayerController::OnMove(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (NatureKeeperCharacter)
	{
		const FRotator CameraRot = NatureKeeperCharacter->GetTopDownCameraComponent()->GetComponentRotation();

		const FRotator YawRot(0.f, CameraRot.Yaw, 0.f);

		const FVector CameraForwardVector = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector CameraRightVector   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		FVector CameraVector = CameraRightVector * MovementValue.X + CameraForwardVector * MovementValue.Y;
		CameraVector.Z = 0.0f;
		CameraVector.Normalize();

		FVector DirectionVector = NatureKeeperCharacter->GetActorForwardVector();
		DirectionVector.Z = 0.0f;
		DirectionVector.Normalize();

		const float CrossZ = FVector::CrossProduct(DirectionVector, CameraVector).Z;
		const float CosBetweenVectors = FVector::DotProduct(DirectionVector, CameraVector);
		const float AngleRad = FMath::Atan2(CrossZ, CosBetweenVectors);
		
		MovementDirectionDegreesAngle = FMath::RadiansToDegrees(AngleRad);

		NatureKeeperCharacter->AddMovementInput(CameraRightVector, MovementValue.X, false);
		NatureKeeperCharacter->AddMovementInput(CameraForwardVector, MovementValue.Y, false);
	}
}

void ANatureKeeperPlayerController::OnJump()
{
	if (NatureKeeperCharacter)
		NatureKeeperCharacter->Jump();
}

void ANatureKeeperPlayerController::OnStopJumping()
{
	if (NatureKeeperCharacter)
		NatureKeeperCharacter->StopJumping();
}

void ANatureKeeperPlayerController::OnStartInteraction()
{
	PlayerFocusComponent->UpdateTrace();

	if (PlayerFocusComponent->bIsPlayerFocus)
	{
		if (PlayerFocusComponent->PlayerFocusedActor->Implements<UInteractiveActorInterface>())
		{
			if (IInteractiveActorInterface::Execute_StartInteract(PlayerFocusComponent->PlayerFocusedActor, GetCharacter()))
			{
				bIsInteract = true;
			}
		}
	}
}

void ANatureKeeperPlayerController::OnEndInteraction()
{
	PlayerFocusComponent->UpdateTrace();
	
	if (PlayerFocusComponent->bIsPlayerFocus)
	{
		if (bIsInteract && PlayerFocusComponent->PlayerFocusedActor->Implements<UInteractiveActorInterface>())
		{
			IInteractiveActorInterface::Execute_StopInteract(PlayerFocusComponent->PlayerFocusedActor, GetCharacter());
		}
	}
	bIsInteract = false;
}

void ANatureKeeperPlayerController::OnEffectActions(const FInputActionInstance& Instance)
{
	const UInputAction* SourceAction = Instance.GetSourceAction();
	if (!SourceAction) return;

	const int32 Index = EffectsActions.IndexOfByKey(SourceAction);
	PlayerTargetComponent->AddAbilityEffectByIndex(Index);

	PlayerTargetComponent->StartTargetStrategy();
}

void ANatureKeeperPlayerController::OnEffectTargetStrategiesActions(const FInputActionInstance& Instance)
{
	const UInputAction* SourceAction = Instance.GetSourceAction();
	if (!SourceAction) return;

	const int32 Index = EffectTargetStrategiesActions.IndexOfByKey(SourceAction);
	const TArray<UTargetStrategy*>& TargetStrategies = PlayerTargetComponent->GetTargetStrategies();

	if (!TargetStrategies.IsValidIndex(Index))
		return;
	
	PlayerTargetComponent->SetTargetStrategy(TargetStrategies[Index]);
	PlayerTargetComponent->StartTargetStrategy();
}

void ANatureKeeperPlayerController::OnEffectTargetStrategiesActionsByClass(
	TSubclassOf<UTargetStrategy> TargetStrategyClass)
{
	const TArray<UTargetStrategy*>& TargetStrategies = PlayerTargetComponent->GetTargetStrategies();
	UTargetStrategy* FoundedTargetStrategy = nullptr;

	for (int i = 0; i < TargetStrategies.Num(); i++)
	{
		if (TargetStrategies[i]->IsA(TargetStrategyClass))
		{
			FoundedTargetStrategy = TargetStrategies[i];
			break;
		}
	}

	if (!FoundedTargetStrategy)
		return;

	PlayerTargetComponent->SetTargetStrategy(FoundedTargetStrategy);
	PlayerTargetComponent->StartTargetStrategy();
}


void ANatureKeeperPlayerController::OnEffectClear()
{
	PlayerTargetComponent->ClearTargetStrategy();
	PlayerTargetComponent->ClearAbilityEffects();
}
