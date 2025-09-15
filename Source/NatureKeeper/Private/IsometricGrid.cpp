#include "NatureKeeper/Public/IsometricGrid.h"

#include "IsometricCell.h"
#include "Kismet/KismetMathLibrary.h"

AIsometricGrid::AIsometricGrid()
{
	bCreateOnConstruct = false;
	GridSize = FIntVector2D(2, 2);
	CellSize = FVector2D(100, 100);
	CellRandomHeightOffset = FVector2D(0, 1);
}

void AIsometricGrid::BeginPlay()
{
	Super::BeginPlay();
	
	CreateGrid();
}

void AIsometricGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bCreateOnConstruct)
		CreateGrid();
}

void AIsometricGrid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Type::Destroyed)
	{
		ClearGrid();
	}
	
	Super::EndPlay(EndPlayReason);
}

void AIsometricGrid::SetNeighbours()
{
	int Index = 0;
	for (int i = 0; i < GridSize.X; i++)
	{
		for (int j = 0; j < GridSize.Y; j++)
		{
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

void AIsometricGrid::CreateGrid()
{
	if (!IsometricCellClass)
		return;

	const int DimSize = GridSize.X * GridSize.Y;

	if (!Cells.IsEmpty() && Cells[0]->GetClass() != IsometricCellClass)
	{
		ClearGrid();
	}

	if (Cells.IsEmpty())
	{
		for (int i = 0; i < DimSize; i++)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Name = FName(FString::Printf(TEXT("IsometricCell_%i"), i));
			AIsometricCell* CreatedCell = GetWorld()->SpawnActor<AIsometricCell>(IsometricCellClass, FVector::ZeroVector,
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
				AIsometricCell* CellToDelete = Cells[Cells.Num() - 1 - i];
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
				SpawnParams.Name = FName(FString::Printf(TEXT("IsometricCell_%i"), i + Cells.Num()));
				AIsometricCell* CreatedCell = GetWorld()->SpawnActor<AIsometricCell>(IsometricCellClass, FVector::ZeroVector,
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
			float RandHeight = UKismetMathLibrary::RandomFloatInRange(CellRandomHeightOffset.X, CellRandomHeightOffset.Y);
			FVector CurrentCellLocation = FVector(InitialCellLocation.X + i * CellSize.X, InitialCellLocation.Y + j * CellSize.Y,
				InitialCellLocation.Z + RandHeight);
			Cells[Index]->SetActorLocation(CurrentCellLocation);
			Index++;
		}
	}

	SetNeighbours();
}

void AIsometricGrid::ClearGrid()
{
	if (Cells.IsEmpty())
		return;
	
	for (int i = 0; i < Cells.Num(); i++)
	{
		Cells[i]->Destroy();
	}

	Cells.Empty();
}

