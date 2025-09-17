// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include "Cell.h"
#include "NoiseShapeComponent.h"


AGrid::AGrid()
{
	NoiseShapeComponent = CreateDefaultSubobject<UNoiseShapeComponent>(TEXT("NoiseShapeComponent"));
	
	bCreateOnConstruct = false;
	GridSize = FIntVector2D(2, 2);
	CellSize = FVector2D(100, 100);
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
	CreateGrid();
}

void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bCreateOnConstruct)
		CreateGrid();
}

void AGrid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Type::Destroyed)
	{
		ClearGrid();
	}
	
	Super::EndPlay(EndPlayReason);
}

void AGrid::SetNeighbours()
{
	int Index = 0;
	for (int i = 0; i < GridSize.X; i++)
	{
		for (int j = 0; j < GridSize.Y; j++)
		{
			Cells[Index]->SetPathNodeCoord(FIntVector2D(i, j));
			Cells[Index]->Neighbours.Empty();

			const int NeighbourBottom = Index - 1;
			const int NeighbourTop = Index + 1;
			const int NeighbourRight = Index + GridSize.Y;
			const int NeighbourLeft = Index - GridSize.Y;

			if (j > 0)
			{
				Cells[Index]->Neighbours.Add(Cells[NeighbourBottom]);
			}

			if (j < GridSize.Y - 1)
			{
				Cells[Index]->Neighbours.Add(Cells[NeighbourTop]);
			}

			if (i > 0)
			{
				Cells[Index]->Neighbours.Add(Cells[NeighbourLeft]);
			}

			if (i < GridSize.X - 1)
			{
				Cells[Index]->Neighbours.Add(Cells[NeighbourRight]);
			}

			Index++;
		}
	}
}

void AGrid::CreateGrid()
{
	if (!CellClass)
		return;

	const int DimSize = GridSize.X * GridSize.Y;

	if (!Cells.IsEmpty() && Cells[0]->GetClass() != CellClass)
	{
		ClearGrid();
	}

	if (Cells.IsEmpty())
	{
		for (int i = 0; i < DimSize; i++)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Name = MakeUniqueObjectName(GetWorld(), ACell::StaticClass(), FName(*FString::Printf(TEXT("IsometricCell_%i"), i)));
			ACell* CreatedCell = GetWorld()->SpawnActor<ACell>(CellClass, FVector::ZeroVector,
				FRotator::ZeroRotator, SpawnParams);
			Cells.Add(CreatedCell);
		}
	}
	else
	{
		if (Cells.Num() >= DimSize)
		{
			int NumToDelete = Cells.Num() - DimSize;
			for (int i = 0; i < NumToDelete; i++)
			{
				ACell* CellToDelete = Cells[Cells.Num() - 1 - i];
				Cells.Remove(CellToDelete);
				CellToDelete->Destroy();
			}
		}
		else
		{
			int NumToAdd = DimSize - Cells.Num();
			for (int i = 0; i < NumToAdd; i++)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Name = MakeUniqueObjectName(GetWorld(), ACell::StaticClass(), FName(*FString::Printf(TEXT("IsometricCell_%i"), i)));
				ACell* CreatedCell = GetWorld()->SpawnActor<ACell>(CellClass, FVector::ZeroVector,
					FRotator::ZeroRotator, SpawnParams);
				Cells.Add(CreatedCell);
			}
		}
	}

	FVector InitialCellLocation = GetActorLocation();
	int Index = 0;
	for (int i = 0; i < GridSize.X; i++)
	{
		for (int j = 0; j < GridSize.Y; j++)
		{
			FVector CurrentCellLocation = FVector(InitialCellLocation.X + i * CellSize.X, InitialCellLocation.Y + j * CellSize.Y,
				InitialCellLocation.Z);
			FVector EvaluatedVector = NoiseShapeComponent->CalculateUnit(CurrentCellLocation);
			CurrentCellLocation.Z = EvaluatedVector.Z;
			Cells[Index]->SetActorLocation(CurrentCellLocation);
			Index++;
		}
	}

	SetNeighbours();
}

void AGrid::ClearGrid()
{
	if (Cells.IsEmpty())
		return;
	
	for (int i = 0; i < Cells.Num(); i++)
	{
		if (Cells[i] && !Cells[i]->IsPendingKillPending())
			Cells[i]->Destroy();
	}

	Cells.Empty();
}