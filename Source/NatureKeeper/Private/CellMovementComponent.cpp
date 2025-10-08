#include "CellMovementComponent.h"

#include "Cell.h"
#include "NatureKeeperUtils.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/CellMovable.h"
#include "Interfaces/Visitor.h"
#include "Kismet/KismetMathLibrary.h"


UCellMovementComponent::UCellMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCellMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCellMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentMovingToCell)
	{
		constexpr float Epsilon = 0.05f;

		FVector ActorLocation = ICellMovable::Execute_GetNavigationRoot(CharacterOwner)->GetComponentLocation();
		FVector NextCellLocation = CurrentMovingToCell->GetNavigationRoot()->GetComponentLocation();
		FVector CurrentCellLocation = CurrentCellStandOn->GetNavigationRoot()->GetComponentLocation();
		
		FVector CurrToNextVector = NextCellLocation - CurrentCellLocation;
		FVector CurrToActorVector = ActorLocation - CurrentCellLocation;
		FVector NormalizedDirection = CurrToNextVector.GetSafeNormal();

		float ProjectionValue = FVector::DotProduct(CurrToActorVector, NormalizedDirection);
		
		float LocationDiff = CurrToNextVector.Size() - ProjectionValue;
		
		if (LocationDiff <= Epsilon)
		{
			//On Update we visit cells that we are moving on (for example to change aura type)
			IVisitor::Execute_OnEndVisit(CharacterOwner, CurrentCellStandOn);
			CurrentCellStandOn = CurrentMovingToCell;
			IVisitor::Execute_OnStartVisit(CharacterOwner, CurrentCellStandOn);
			
			if (CurrentMovingToCell == CurrentTargetCell)
			{
				ICellMovementInterface::Execute_TryStopActiveMoveByPath(this);
			}
			else
			{
				CurrentMovingToCellIndex++;
				CurrentMovingToCell = CurrentMovingPath[CurrentMovingToCellIndex];
				UE_LOG(LogTemp, Display, TEXT("change cell %s"), *CurrentMovingToCell->GetName());
			}
		}
		else
		{
			float Step = FMath::Min(MaxCellMovementSpeed * DeltaTime, LocationDiff);
			CurrentCellMovementSpeed = Step / DeltaTime;
			FVector Delta = NormalizedDirection * Step;
			CharacterOwner->GetCharacterMovement()->MoveUpdatedComponent(Delta, UKismetMathLibrary::MakeRotFromX(NormalizedDirection), true);
		}
	}
}

void UCellMovementComponent::InitCellComponent(ACharacter* NewCharacterOwner)
{
	CharacterOwner = NewCharacterOwner;
	ICellMovementInterface::Execute_CellIdle(this);

	//On Init we visit by our character cell that we on right now (for example to change aura type)
	if (CurrentCellStandOn)
		IVisitor::Execute_OnStartVisit(CharacterOwner, CurrentCellStandOn);
}

ACell* UCellMovementComponent::GetCellStandOn_Implementation()
{
	return CurrentCellStandOn;
}

ACell* UCellMovementComponent::GetCellMovingTo_Implementation()
{
	return CurrentMovingToCell;
}

int32 UCellMovementComponent::GetCellMovingToIndex_Implementation()
{
	return CurrentMovingToCell ? CurrentMovingToCellIndex : INDEX_NONE;
}

ACell* UCellMovementComponent::GetTargetCell_Implementation()
{
	return CurrentTargetCell;
}

TArray<ACell*> UCellMovementComponent::GetPath_Implementation()
{
	return CurrentMovingPath;
}

float UCellMovementComponent::GetCellMovementCurrentSpeed_Implementation()
{
	return CurrentCellMovementSpeed;
}

float UCellMovementComponent::GetCellMovementMaxSpeed_Implementation()
{
	return MaxCellMovementSpeed;
}

void UCellMovementComponent::CellIdle_Implementation()
{
	FVector StartLocation = CharacterOwner->GetActorLocation(); 
	StartLocation.Z += 10.0f; 

	FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, 1000.0f);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CharacterOwner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		QueryParams
	);

	DrawDebugLine(
		GetWorld(),
		StartLocation,
		EndLocation,
		bHit ? FColor::Green : FColor::Red,
		false,
		0.1f,
		0,
		1.0f
	);

	if (bHit)
	{
		if (ACell* CellUnderPlayer = Cast<ACell>(HitResult.GetActor()))
		{
			CurrentCellStandOn = CellUnderPlayer;
		}
	}
}

bool UCellMovementComponent::TryStartActiveMoveByPath_Implementation(const TArray<ACell*>& TargetCells)
{
	if (CurrentMovingPath.IsEmpty())
	{
		ICellMovementInterface::Execute_CellIdle(this);

		if (!CurrentCellStandOn || TargetCells.IsEmpty())
			return false;
		
		TArray<ACell*> NewPath = UNatureKeeperUtils::FindPath(CurrentCellStandOn, TargetCells[0]);
		
		for (int i = 1; i < TargetCells.Num(); i++)
		{
			TArray<ACell*> PotentialNewPath = UNatureKeeperUtils::FindPath(CurrentCellStandOn, TargetCells[i]);
			if (PotentialNewPath.IsEmpty())
				continue;
			
			if (PotentialNewPath.Num() < NewPath.Num() || NewPath.IsEmpty())
				NewPath = PotentialNewPath;
		}

		if (NewPath.IsEmpty())
			return false;

		CurrentMovingPath = NewPath;
		CurrentTargetCell = NewPath[NewPath.Num() - 1];
		CurrentMovingToCellIndex = 0;
		CurrentMovingToCell = NewPath[CurrentMovingToCellIndex];

		return true;
	}
	
	if (!CurrentMovingToCell || TargetCells.IsEmpty() || CurrentMovingToCellIndex == INDEX_NONE)
		return false;

	TArray<ACell*> NewPath = UNatureKeeperUtils::FindPath(CurrentCellStandOn, TargetCells[0]);
		
	for (int i = 1; i < TargetCells.Num(); i++)
	{
		TArray<ACell*> PotentialNewPath = UNatureKeeperUtils::FindPath(CurrentCellStandOn, TargetCells[i]);
		if (PotentialNewPath.IsEmpty())
			continue;
			
		if (PotentialNewPath.Num() < NewPath.Num() || NewPath.IsEmpty())
			NewPath = PotentialNewPath;
	}

	if (NewPath.IsEmpty())
		return false;

	CurrentMovingPath.Empty();
	CurrentMovingPath.Add(CurrentMovingToCell);
	CurrentMovingPath.Append(NewPath);
	CurrentMovingToCellIndex = 0;
		
	return true;
}

bool UCellMovementComponent::TryStopActiveMoveByPath_Implementation()
{
	CurrentMovingPath.Empty();
	CurrentTargetCell = nullptr;
	CurrentMovingToCell = nullptr;
	CurrentMovingToCellIndex = INDEX_NONE;
	CurrentCellMovementSpeed = 0.0f;

	return true;
}