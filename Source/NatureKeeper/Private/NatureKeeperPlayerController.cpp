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
#include "IsometricCell.h"
#include "NatureKeeperUtils.h"
#include "Engine/LocalPlayer.h"

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
}

void ANatureKeeperPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (CurrentMovingToCell)
	{
		APawn* ControlledPawn = GetPawn();
		
		FVector Direction = CurrentMovingToCell->GetActorLocation() - ControlledPawn->GetActorLocation();
		if (Direction.Length() < 0.001f)
		{
			//ControlledPawn->SetActorLocation(CurrentMovingToCell->GetActorLocation());
			
			if (CurrentMovingToCell == CurrentTargetCell)
			{
				StopActiveMoveByPath();
			}
			else
			{
				CurrentMovingToCellIndex++;
				CurrentMovingToCell = CurrentPath[CurrentMovingToCellIndex];
			}
		}
		FVector WorldDirection = Direction.GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
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

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ANatureKeeperPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ANatureKeeperPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ANatureKeeperPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ANatureKeeperPlayerController::OnTouchReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANatureKeeperPlayerController::OnInputStarted()
{
	StopMovement();

	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		if (Hit.GetActor()->Implements<UInteractiveActor>())
		{
			IInteractiveActor::Execute_StartInteract(Hit.GetActor(), GetCharacter());
		}
	}
}

// Triggered every frame when the input is held down
void ANatureKeeperPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	/*// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}*/
}

void ANatureKeeperPlayerController::OnSetDestinationReleased()
{
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		if (Hit.GetActor()->Implements<UInteractiveActor>())
		{
			IInteractiveActor::Execute_StopInteract(Hit.GetActor(), GetCharacter());
		}
	}

	/*// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}*/

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ANatureKeeperPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ANatureKeeperPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

ACell* ANatureKeeperPlayerController::GetCellMovingTo_Implementation()
{
	return CurrentMovingToCell;
}

int32 ANatureKeeperPlayerController::GetCellMovingToIndex_Implementation()
{
	return CurrentMovingToCell ? CurrentMovingToCellIndex : INDEX_NONE;
}

ACell* ANatureKeeperPlayerController::GetTargetCell_Implementation()
{
	return CurrentTargetCell;
}

TArray<ACell*> ANatureKeeperPlayerController::GetPath_Implementation()
{
	return CurrentPath;
}

void ANatureKeeperPlayerController::StartActiveMoveByPath_Implementation(TArray<ACell*> NewPath)
{
	if (NewPath.IsEmpty())
		return;
	
	CurrentPath = NewPath;
	CurrentTargetCell = NewPath[NewPath.Num() - 1];
	CurrentMovingToCellIndex = 0;
	CurrentMovingToCell = NewPath[CurrentMovingToCellIndex];
}

void ANatureKeeperPlayerController::StopActiveMoveByPath_Implementation()
{
	CurrentPath.Empty();
	CurrentTargetCell = nullptr;
	CurrentMovingToCell = nullptr;
}
