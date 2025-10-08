// Copyright Epic Games, Inc. All Rights Reserved.

#include "NatureKeeper/Public/NatureKeeperCharacter.h"

#include "Cell.h"
#include "CellMovementComponent.h"
#include "FocusComponent.h"
#include "NatureKeeperGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Effects/AbilityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Interfaces/CellMovementInterface.h"
#include "ResourceSystem/EvilComponent.h"
#include "ResourceSystem/HealthComponent.h"
#include "ResourceSystem/ManaComponent.h"
#include "TargetSystem/TargetComponent.h"

class ANatureKeeperGameMode;

ANatureKeeperCharacter::ANatureKeeperCharacter()
{
	CellMovementComponent = CreateDefaultSubobject<UCellMovementComponent>(FName("CellMovementComponent"));
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>("AbilityComponent");
	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	ManaComponent = CreateDefaultSubobject<UManaComponent>("ManaComponent");
	EvilComponent = CreateDefaultSubobject<UEvilComponent>("EvilComponent");

	FocusComponent = CreateDefaultSubobject<UFocusComponent>("FocusComponent");
	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ANatureKeeperCharacter::BeginPlay()
{
	if (CellMovementComponent)
	{
		CellMovementComponent->InitCellComponent(this);
	}
	
	Super::BeginPlay();
}

void ANatureKeeperCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

TScriptInterface<UCellMovementInterface> ANatureKeeperCharacter::GetCellMovementInterface_Implementation()
{
	return CellMovementComponent;
}

USceneComponent* ANatureKeeperCharacter::GetNavigationRoot_Implementation()
{
	return RootComponent;
}

bool ANatureKeeperCharacter::TryMoveByCells_Implementation(const TArray<ACell*>& TargetCells)
{
	if (TargetCells.IsEmpty())
		return false;
	
	return ICellMovementInterface::Execute_TryStartActiveMoveByPath(CellMovementComponent, TargetCells);
}

bool ANatureKeeperCharacter::OnStartVisit_Implementation(const TScriptInterface<UVisitable>& Visitable)
{
	if (Visitable.GetObject())
	{
		if (ACell* Cell = Cast<ACell>(Visitable.GetObject()))
		{
			//Absorb evil energy from cell, idk should i put this logic in effect and ability system, but effect doesn't have ref to owner,
			//so we can't increase player evil energy
			IVisitable::Execute_StartVisit(Cell, this);
			int MaxEvilValue = Cell->EvilComponent->GetMaxResourceValue();
			Cell->EvilComponent->DecreaseResourceValue(MaxEvilValue);
			EvilComponent->IncreaseResourceValue(MaxEvilValue);
			return true;
		}

		return IVisitable::Execute_StartVisit(Visitable.GetObject(), this);
	}

	return false;
}

bool ANatureKeeperCharacter::OnEndVisit_Implementation(const TScriptInterface<UVisitable>& Visitable)
{
	if (Visitable.GetObject())
	{
		return IVisitable::Execute_EndVisit(Visitable.GetObject(), this);
	}

	return false;
}

void ANatureKeeperCharacter::Heal_Implementation(int HealAmount)
{
	HealthComponent->IncreaseResourceValue(HealAmount);
}


void ANatureKeeperCharacter::TakeDamage_Implementation(int Damage)
{
	HealthComponent->DecreaseResourceValue(Damage);
}

bool ANatureKeeperCharacter::RegisterEffect_Implementation(UEffectBase* EffectToAdd)
{
	if (Effects.Contains(EffectToAdd))
		return false;

	Effects.Add(EffectToAdd);
	return true;
}

bool ANatureKeeperCharacter::UnregisterEffect_Implementation(UEffectBase* EffectToRemove)
{
	if (!Effects.Contains(EffectToRemove))
		return false;

	Effects.Remove(EffectToRemove);
	return true;
}

FVector ANatureKeeperCharacter::GetEffectLocation_Implementation()
{
	return GetActorLocation();
}
